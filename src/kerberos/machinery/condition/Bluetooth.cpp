#include "machinery/condition/Bluetooth.h"
namespace kerberos
{
    void Bluetooth::setup(const StringMap &settings)
    {
        Condition::setup(settings);
        std::string adapterName = settings.at("bluetoothAdapter").c_str() ?: std::string("hci0");
        int rssiThreshold = std::atoi(settings.at("bluetoothRssiThreshold").c_str()) ?: -80;
        std::string deviceId = settings.at("bluetoothDevice");
        BluetoothDetectorApiFactory factory;
        std::vector<std::string> addresses{deviceId};
        _apiInstance = factory.create(
            adapterName, addresses, rssiThreshold,
            [this](bool isAvailable) {
                LINFO << "========> Is available: " << isAvailable;
                _inRange = isAvailable;
            },
            [](std::exception_ptr ep) {
                try
                {
                    std::rethrow_exception(ep);
                }
                catch (const std::exception &ex)
                {
                    LERROR << "Rssi stream error: " << ex.what();
                }
            },
            []() {
                LINFO << "Bluetooth steam ended";
            });
        _inRange = false;
    }

    bool Bluetooth::allowed(const ImageVector &images)
    {
        return !_inRange;
    }
} // namespace kerberos