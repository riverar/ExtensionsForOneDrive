using System.Threading.Tasks;
using Microsoft.Live;
using ExtensionsForOneDrive.Models;

namespace ExtensionsForOneDrive
{
    public class RegistryRefreshTokenHandler : IRefreshTokenHandler
    {
        private readonly IConfigurationService _configurationService;

        public RegistryRefreshTokenHandler(IConfigurationService configurationService)
        {
            _configurationService = configurationService;
        }

        public Task<RefreshTokenInfo> RetrieveRefreshTokenAsync()
        {
            return Task.Factory.StartNew<RefreshTokenInfo>(() =>
            {
                var token = _configurationService.GetValue<string>("RefreshToken");

                if (!string.IsNullOrWhiteSpace(token))
                {
                    return new RefreshTokenInfo(token);
                }
                else
                {
                    return null;
                }

            });
        }

        public Task SaveRefreshTokenAsync(RefreshTokenInfo tokenInfo)
        {
            return Task.Factory.StartNew(() =>
            {
                _configurationService.SetValue("RefreshToken", tokenInfo.RefreshToken);
            });
        }
    }
}