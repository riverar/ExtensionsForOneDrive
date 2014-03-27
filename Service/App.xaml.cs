using System.Threading;
using System.Windows;
using System.Threading.Tasks;

using GalaSoft.MvvmLight.Ioc;
using GalaSoft.MvvmLight.Messaging;

using Microsoft.Live;
using Microsoft.Live.Public;
using Microsoft.Practices.ServiceLocation;

using ExtensionsForOneDrive.Models;
using ExtensionsForOneDrive.ViewModel;
using ExtensionsForOneDrive.Service.Models;

namespace ExtensionsForOneDrive
{
    public partial class App : Application
    {
        private LoginWindow _loginWindow;
        private static Mutex _mutex;

        protected override void OnStartup(StartupEventArgs e)
        {
            base.OnStartup(e);

            RegisterProviders();
            RegisterMutex();

            ShowLoginWindowIfNeeded();
        }

        private void ShowLoginWindowIfNeeded()
        {
            Messenger.Default.Register<CloseLoginWindow>(this, (msg) =>
            {
                _loginWindow.Close();
                _loginWindow = null;

                if(msg.ContinueProcessing)
                {
                    var clipboardService = ServiceLocator.Current.GetInstance<IClipboardService>();
                    clipboardService.GetPublicLinkAndStore();
                }
            });

            var configurationService = ServiceLocator.Current.GetInstance<IConfigurationService>();
            if(configurationService.GetValue<int>("IsConfigured") == 0)
            {
                _loginWindow = new LoginWindow();
                _loginWindow.WindowStartupLocation = WindowStartupLocation.CenterScreen;
                _loginWindow.ShowDialog();
            }
        }

        private void RegisterMutex()
        {
            Task.Factory.StartNew(() =>
            {
                _mutex = new Mutex(true, @"ExtensionsForOneDrive_Mutex");
                _mutex.WaitOne();
            });
        }

        private void UnregisterMutex()
        {
            _mutex.Dispose();
        }

        private void RegisterProviders()
        {
            SimpleIoc.Default.Register<IConfigurationService, RegistryConfigurationService>();
            SimpleIoc.Default.Register<IRefreshTokenHandler, RegistryRefreshTokenHandler>();
            SimpleIoc.Default.Register<LoginWindowViewModel>();

            SimpleIoc.Default.Register<LiveAuthClient>(() =>
            {
                return new LiveAuthClient("000000004011678D", SimpleIoc.Default.GetInstance<IRefreshTokenHandler>());
            });

            SimpleIoc.Default.Register<ILiveAuthClient>(() =>
            {
                return SimpleIoc.Default.GetInstance<LiveAuthClient>();
            });

            SimpleIoc.Default.Register<INotificationService, NotificationService>(true);
            SimpleIoc.Default.Register<ILiveService, LiveService>(true);
            SimpleIoc.Default.Register<IClipboardService, ClipboardService>(true);

            ServiceLocator.SetLocatorProvider(() => SimpleIoc.Default);
        }

        protected override void OnExit(ExitEventArgs e)
        {
            base.OnExit(e);

            UnregisterMutex();
        }
    }
}
