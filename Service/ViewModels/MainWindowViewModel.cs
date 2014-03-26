using GalaSoft.MvvmLight;
using GalaSoft.MvvmLight.Command;
using GalaSoft.MvvmLight.Messaging;

using ExtensionsForOneDrive.Models;

namespace ExtensionsForOneDrive.ViewModel
{
	public class MainWindowViewModel : ViewModelBase
	{
		private readonly IConfigurationService _configurationService;

		public MainWindowViewModel(IConfigurationService configurationService)
		{
			_configurationService = configurationService;

			OneDriveLoginCommand = new RelayCommand(() =>
			{
				Messenger.Default.Send<OpenLoginWindow>(new OpenLoginWindow());
			},
			() =>
			{
				return _configurationService.GetValue<int>("IsConfigured") == 0;
			});

			SetNextRefresh();

			_configurationService.PropertyChanged += (_, args) =>
			{
				if (args.PropertyName == "TokenExpiration")
				{
					SetNextRefresh();
				}
			};
		}

		public RelayCommand OneDriveLoginCommand { get; set; }

		private string _nextRefresh;
		public string NextRefresh
		{
			get { return _nextRefresh; }
			set
			{
				_nextRefresh = value;
				RaisePropertyChanged("NextRefresh");
			}
		}

		private void SetNextRefresh()
		{
			if (_configurationService.GetValue<int>("IsConfigured")  == 0)
			{
				this.NextRefresh = "(not configured)";
			}
			else
			{
				this.NextRefresh = _configurationService.GetValue<string>("TokenExpiration");
			}
		}
	}
}