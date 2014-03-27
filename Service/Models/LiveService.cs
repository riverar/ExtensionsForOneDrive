using System;
using System.Linq;
using System.Timers;
using System.Collections.Generic;

using Microsoft.Live;
using Microsoft.Live.Public;

namespace ExtensionsForOneDrive.Models
{
    public interface ILiveService
    {
        bool IsAuthenticated { get; set; }

        string GetLoginUrl();

        void GetTokens(string authorizationCode);

        string GetSharedReadLink(string fileID);
    }

    public class LiveService : ILiveService
    {
        private readonly ILiveAuthClient _authClient;
        private readonly IRefreshTokenHandler _refreshTokenHandler;
        private readonly IConfigurationService _configurationService;
        private readonly IEnumerable<string> _scopes = new List<string> {
            "wl.signin", "wl.offline_access", "wl.skydrive", "wl.skydrive_update"
        };

        private LiveConnectSession _session;
        private Timer _refreshTimer;

        public LiveService(IRefreshTokenHandler refreshTokenHandler, ILiveAuthClient authClient, IConfigurationService configurationService)
        {
            _refreshTokenHandler = refreshTokenHandler;
            _configurationService = configurationService;
            _authClient = authClient;

            _refreshTimer = new Timer();
            ConfigureRefreshTimer();

            _configurationService.PropertyChanged += (_, args) =>
            {
                if (args.PropertyName == "TokenExpiration")
                {
                    ConfigureRefreshTimer();
                }
            };
        }

        private void ConfigureRefreshTimer()
        {
            _refreshTimer.Stop();
            _refreshTimer.AutoReset = false;
            _refreshTimer.Elapsed += RefreshTimerElapsed;

            if(_configurationService.GetValue<int>("Configured") > 0)
            {
                var expiration = DateTime.Parse(_configurationService.GetValue<string>("TokenExpiration"));

                if (DateTime.Now < expiration)
                {
                    var span = expiration - DateTime.Now;
                    _refreshTimer.Interval = span.TotalMilliseconds;
                }
                else
                {
                    _refreshTimer.Interval = TimeSpan.FromSeconds(3).TotalMilliseconds;
                }

                _refreshTimer.Start();
            }
        }

        public bool IsAuthenticated { get; set; }

        public string GetLoginUrl()
        {
            return _authClient.GetLoginUrl(_scopes);
        }

        public void GetTokens(string authorizationCode)
        {
            var task = _authClient.ExchangeAuthCodeAsync(authorizationCode);
            task.Wait();

            // TODO: Failure case

            _session = task.Result;
            
            SaveTokens();

            this.IsAuthenticated = true;
        }

        private void RefreshTokens()
        {
            var task = _authClient.IntializeAsync(_scopes);
            task.Wait();

            // TODO: Failure case

            // TODO: Lock session

            _session = task.Result.Session;
            
            SaveTokens();

            this.IsAuthenticated = true;
        }

        private void SaveTokens()
        {
            _configurationService.SetValue("AccessToken", _session.AccessToken);
            _configurationService.SetValue("RefreshToken", _session.RefreshToken);
            _configurationService.SetValue("TokenExpiration", DateTime.Now.AddMinutes(45).ToString());
            _configurationService.SetValue("IsConfigured", 1);
        }

        private void RefreshTimerElapsed(object sender, ElapsedEventArgs args)
        {
            this.RefreshTokens();
        }

        public string GetSharedReadLink(string fileID)
        {
            if (string.IsNullOrWhiteSpace(fileID))
                throw new ArgumentNullException("id");

            var filePrefix = fileID.Split('!').First();

            if (_session == null)
            {
                this.RefreshTokens();
            }

            var connectClient = new LiveConnectClient(_session);
            var task = connectClient.GetAsync(string.Format("file.{0}.{1}/shared_read_link", filePrefix, fileID));
            task.Wait();

            // TODO: Error condition

            // HACK
            var result = task.Result.Result;
            return result["link"] as string;
        }
    }
}
