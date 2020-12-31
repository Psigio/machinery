#include "machinery/condition/Bluetooth.h"
namespace kerberos
{
    void Bluetooth::setup(const StringMap &settings)
    {
        LINFO << "Bluetooth Condition Setup";
        Condition::setup(settings);
        std::string adapterName = settings.at("conditions.Bluetooth.bluetoothAdapter").c_str() ?: std::string("hci0");
        int rssiThreshold = std::atoi(settings.at("conditions.Bluetooth.bluetoothRssiThreshold").c_str()) ?: -80;
        std::string deviceId = settings.at("conditions.Bluetooth.bluetoothDevice");
        BluetoothDetectorApiFactory factory;
        std::vector<std::string> addresses{deviceId};
        _apiInstance = factory.create(
            adapterName, addresses, rssiThreshold,
            [this](bool isAvailable) {
                LINFO << "========> Is available: " << isAvailable;
                _inRange = isAvailable;
            },
            [this](std::exception_ptr ep) {
                try
                {
                    std::rethrow_exception(ep);
                }
                catch (const std::exception &ex)
                {
                    LERROR << "Rssi stream error: " << ex.what();
                }
                _inRange = false;
            },
            [this]() {
                LINFO << "Bluetooth stream ended";
                _inRange = false;
            });
        _inRange = false;
        LINFO << "Bluetooth Condition Setup done - listening to " << adapterName << " for " << deviceId;
    }

    bool Bluetooth::allowed(const ImageVector &images)
    {
        return !_inRange;
    }
} // namespace kerberos
