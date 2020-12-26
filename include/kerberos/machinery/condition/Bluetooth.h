//
//  Class: Bluetooth
//  Description: When Bluetooth Low Energy device has RSSI >-80 return true.

#ifndef __Bluetooth_H_INCLUDED__ // if Bluetooth.h hasn't been included yet...
#define __Bluetooth_H_INCLUDED__ // #define this so the compiler knows it has been included

#include "machinery/condition/Condition.h"
#include "BluetoothDetectorApi.hpp"
#include <memory>

namespace kerberos
{
    char BluetoothName[] = "Bluetooth";
    class Bluetooth : public ConditionCreator<BluetoothName, Bluetooth>
    {
    private:
        std::shared_ptr<IBluetoothDetectorApi> _apiInstance;
        bool _inRange;

    public:
        Bluetooth() {}
        void setup(const StringMap &settings);
        bool allowed(const ImageVector &images);
    };
} // namespace kerberos
#endif