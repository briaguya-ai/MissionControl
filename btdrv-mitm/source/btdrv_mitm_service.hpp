#pragma once
#include <stratosphere.hpp>
#include "bluetooth/bluetooth_types.hpp"

#include "btdrv_mitm_logging.hpp"

namespace ams::mitm::btdrv {

    namespace {

        #define AMS_BTDRV_MITM_INTERFACE_INFO(C, H) \
            AMS_SF_METHOD_INFO(C, H, 1,  Result, InitializeBluetooth,               (sf::OutCopyHandle out_handle)) \
            AMS_SF_METHOD_INFO(C, H, 4,  Result, FinalizeBluetooth,                 (void)) \
            AMS_SF_METHOD_INFO(C, H, 15, Result, GetEventInfo,                      (sf::Out<bluetooth::EventType> out_type, const sf::OutPointerBuffer &out_buffer)) \
            AMS_SF_METHOD_INFO(C, H, 16, Result, InitializeHid,                     (sf::OutCopyHandle out_handle, u16 version)) \
            AMS_SF_METHOD_INFO(C, H, 19, Result, WriteHidData,                      (bluetooth::Address address, const sf::InPointerBuffer &buffer)) \
            AMS_SF_METHOD_INFO(C, H, 25, Result, GetPairedDeviceInfo,               (sf::Out<bluetooth::DeviceSettings> out, bluetooth::Address address)) \
            AMS_SF_METHOD_INFO(C, H, 26, Result, FinalizeHid,                       (void)) \
            AMS_SF_METHOD_INFO(C, H, 27, Result, GetHidEventInfo,                   (sf::Out<bluetooth::HidEventType> out_type, const sf::OutPointerBuffer &out_buffer)) \
            AMS_SF_METHOD_INFO(C, H, 36, Result, RegisterHidReportEventDeprecated,  (sf::OutCopyHandle out_handle),                                                         hos::Version_1_0_0, hos::Version_3_0_2) \
            AMS_SF_METHOD_INFO(C, H, 37, Result, RegisterHidReportEvent,            (sf::OutCopyHandle out_handle),                                                         hos::Version_4_0_0) \
            AMS_SF_METHOD_INFO(C, H, 37, Result, GetHidReportEventInfoDeprecated1,  (sf::Out<bluetooth::HidEventType> out_type, const sf::OutPointerBuffer &out_buffer),    hos::Version_1_0_0, hos::Version_3_0_2) \
            AMS_SF_METHOD_INFO(C, H, 38, Result, GetHidReportEventInfoDeprecated2,  (sf::Out<bluetooth::HidEventType> out_type, const sf::OutPointerBuffer &out_buffer),    hos::Version_4_0_0, hos::Version_6_2_0) \
            AMS_SF_METHOD_INFO(C, H, 38, Result, GetHidReportEventInfo,             (sf::OutCopyHandle out_handle),                                                         hos::Version_7_0_0) \
            AMS_SF_METHOD_INFO(C, H, 46, Result, InitializeBle,                     (sf::OutCopyHandle out_handle),                                                         hos::Version_5_0_0) \
            AMS_SF_METHOD_INFO(C, H, 49, Result, FinalizeBle,                       (void),                                                                                 hos::Version_5_0_0) \
            AMS_SF_METHOD_INFO(C, H, 78, Result, GetBleManagedEventInfoDeprecated,  (sf::Out<bluetooth::BleEventType> out_type, const sf::OutPointerBuffer &out_buffer),    hos::Version_5_0_0, hos::Version_5_0_2) \
            AMS_SF_METHOD_INFO(C, H, 79, Result, GetBleManagedEventInfo,            (sf::Out<bluetooth::BleEventType> out_type, const sf::OutPointerBuffer &out_buffer),    hos::Version_5_1_0) \
            AMS_SF_METHOD_INFO(C, H, 65000, void, RedirectCoreEvents,               (bool redirect)) \
            AMS_SF_METHOD_INFO(C, H, 65001, void, RedirectHidEvents,                (bool redirect)) \
            AMS_SF_METHOD_INFO(C, H, 65002, void, RedirectHidReportEvents,          (bool redirect)) \
            AMS_SF_METHOD_INFO(C, H, 65003, void, RedirectBleEvents,                (bool redirect)) \
            AMS_SF_METHOD_INFO(C, H, 65004, Result, GetRealSharedMemory,            (sf::OutCopyHandle out_handle),                                                         hos::Version_7_0_0) \
            AMS_SF_METHOD_INFO(C, H, 65005, Result, GetFakeSharedMemory,            (sf::OutCopyHandle out_handle)) \

        AMS_SF_DEFINE_MITM_INTERFACE(IBtdrvMitmInterface, AMS_BTDRV_MITM_INTERFACE_INFO)

    }

    class BtdrvMitmService : public sf::MitmServiceImplBase  {

        public:
            using MitmServiceImplBase::MitmServiceImplBase;

        public:
            static bool ShouldMitm(const sm::MitmProcessInfo &client_info) {
                return true;
            }

        public:
            Result InitializeBluetooth(sf::OutCopyHandle out_handle);
            Result FinalizeBluetooth(void);
            Result GetEventInfo(sf::Out<bluetooth::EventType> out_type, const sf::OutPointerBuffer &out_buffer);
            Result InitializeHid(sf::OutCopyHandle out_handle, u16 version);
            Result WriteHidData(bluetooth::Address address, const sf::InPointerBuffer &buffer);
            Result GetPairedDeviceInfo(sf::Out<bluetooth::DeviceSettings> out, bluetooth::Address address);
            Result FinalizeHid(void);
            Result GetHidEventInfo(sf::Out<bluetooth::HidEventType> out_type, const sf::OutPointerBuffer &out_buffer);            
            Result RegisterHidReportEventDeprecated(sf::OutCopyHandle out_handle);
            Result RegisterHidReportEvent(sf::OutCopyHandle out_handle);
            Result GetHidReportEventInfoDeprecated1(sf::Out<bluetooth::HidEventType> out_type, const sf::OutPointerBuffer &out_buffer);
            Result GetHidReportEventInfoDeprecated2(sf::Out<bluetooth::HidEventType> out_type, const sf::OutPointerBuffer &out_buffer);
            Result GetHidReportEventInfo(sf::OutCopyHandle out_handle);
            /* 5.0.0+ */
            Result InitializeBle(sf::OutCopyHandle out_handle);
            Result FinalizeBle(void);
            Result GetBleManagedEventInfoDeprecated(sf::Out<bluetooth::BleEventType> out_type, const sf::OutPointerBuffer &out_buffer);
            Result GetBleManagedEventInfo(sf::Out<bluetooth::BleEventType> out_type, const sf::OutPointerBuffer &out_buffer);

            /* Extensions */
            void RedirectCoreEvents(bool redirect);
            void RedirectHidEvents(bool redirect);
            void RedirectHidReportEvents(bool redirect);
            void RedirectBleEvents(bool redirect);
            Result GetRealSharedMemory(sf::OutCopyHandle out_handle);
            Result GetFakeSharedMemory(sf::OutCopyHandle out_handle);

    };
    static_assert(IsIBtdrvMitmInterface<BtdrvMitmService>);

}
