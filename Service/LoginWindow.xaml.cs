using System.Windows;

using GalaSoft.MvvmLight.Messaging;
using ExtensionsForOneDrive.ViewModel;
using Microsoft.Practices.ServiceLocation;

namespace ExtensionsForOneDrive
{
	public partial class LoginWindow : Window
	{
		public LoginWindow()
		{
			InitializeComponent();

			this.DataContext = ServiceLocator.Current.GetInstance<LoginWindowViewModel>();
		}
	}
}
