using System;
using System.Web;
using System.Windows.Navigation;

using GalaSoft.MvvmLight;
using GalaSoft.MvvmLight.Command;
using GalaSoft.MvvmLight.Messaging;

using ExtensionsForOneDrive.Models;

namespace ExtensionsForOneDrive.ViewModel
{
    public class LoginWindowViewModel : ViewModelBase
    {
		private readonly ILiveService _liveAuthService;
		private readonly IConfigurationService _configurationService;

		public LoginWindowViewModel(ILiveService liveAuthService, IConfigurationService configurationService)
		{
			if (liveAuthService == null)
				throw new ArgumentNullException("liveAuthService");

			if (configurationService == null)
				throw new ArgumentNullException("configurationService");

			_liveAuthService = liveAuthService;
			_configurationService = configurationService;

			Loaded = new RelayCommand(() =>
			{
				var loginUrl = _liveAuthService.GetLoginUrl();
				this.CurrentPage = new Uri(loginUrl, UriKind.Absolute);
			});

			Navigated = new RelayCommand<NavigationEventArgs>((args) =>
			{
				if (args.Uri.AbsoluteUri.StartsWith("https://login.live.com/oauth20_desktop.srf"))
				{
					var continueProcessing = false;
					var parsedQueryParameters = HttpUtility.ParseQueryString(args.Uri.Query);
					var authorizationCode = parsedQueryParameters["code"];

					if (authorizationCode != null)
					{
						_liveAuthService.GetTokens(authorizationCode);
						continueProcessing = true;
					}

					Messenger.Default.Send<CloseLoginWindow>(new CloseLoginWindow(continueProcessing));
				}
			});
        }

		private Uri _currentPage;
		public Uri CurrentPage
		{
			get
			{
				return _currentPage;
			}

			set
			{
				_currentPage = value;
				RaisePropertyChanged("CurrentPage");
			}
		}

		public RelayCommand Loaded { get; set; }

		public RelayCommand<NavigationEventArgs> Navigated { get; set; }
    }
}