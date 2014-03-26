using ExtensionsForOneDrive.Service;
using Microsoft.Practices.ServiceLocation;
using ExtensionsForOneDrive.ViewModel;
using System.Windows;

using ExtensionsForOneDrive.Service.Utilities;

namespace ExtensionsForOneDrive
{
	public partial class MainWindow : Window
	{
		public MainWindow()
		{
			InitializeComponent();

			this.DataContext = ServiceLocator.Current.GetInstance<MainWindowViewModel>();
			this.Icon = Assets.Cloud.ToImageSource();
		}
	}
}
