using Microsoft.Win32;
using System.ComponentModel;

namespace ExtensionsForOneDrive.Models
{
	public interface IConfigurationService
	{
		T GetValue<T>(string name);
		
		void SetValue(string name, object value);

		event PropertyChangedEventHandler PropertyChanged;
	}

	public class RegistryConfigurationService : IConfigurationService, INotifyPropertyChanged
	{
		private readonly string _registryRoot = @"Software\Rafael\ExtensionsForOneDrive";

		public T GetValue<T>(string name)
		{
			using (var root = Registry.CurrentUser.CreateSubKey(_registryRoot))
			{
				var value = root.GetValue(name);

				if (value == null)
					return default(T);
				else
					return (T)value;
			}
		}

		public void SetValue(string name, object value)
		{
			using (var root = Registry.CurrentUser.CreateSubKey(_registryRoot))
			{
				RegistryValueKind kind;

				if (value is short || value is int || value is long)
					kind = RegistryValueKind.DWord;
				else
					kind = RegistryValueKind.String;

				root.SetValue(name, value, kind);

				RaisePropertyChanged(name);
			}
		}

		public event PropertyChangedEventHandler PropertyChanged;

		protected void RaisePropertyChanged(string name)
		{
			PropertyChangedEventHandler handler = PropertyChanged;
			if (handler != null)
			{
				handler(this, new PropertyChangedEventArgs(name));
			}
		}
	}
}
