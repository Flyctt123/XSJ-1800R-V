/****************************************************************************
** Meta object code from reading C++ file 'tcp_socket.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.9)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../tcp_socket.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#include <QtCore/QList>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'tcp_socket.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.9. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_tcp_socket_t {
    QByteArrayData data[191];
    char stringdata0[3104];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_tcp_socket_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_tcp_socket_t qt_meta_stringdata_tcp_socket = {
    {
QT_MOC_LITERAL(0, 0, 10), // "tcp_socket"
QT_MOC_LITERAL(1, 11, 10), // "uploadTime"
QT_MOC_LITERAL(2, 22, 0), // ""
QT_MOC_LITERAL(3, 23, 7), // "uint8_t"
QT_MOC_LITERAL(4, 31, 14), // "uploadPassword"
QT_MOC_LITERAL(5, 46, 10), // "kdy_signal"
QT_MOC_LITERAL(6, 57, 13), // "uploadBaseSet"
QT_MOC_LITERAL(7, 71, 12), // "uploadRunSet"
QT_MOC_LITERAL(8, 84, 14), // "Wifi_Connected"
QT_MOC_LITERAL(9, 99, 17), // "Wifi_Disconnected"
QT_MOC_LITERAL(10, 117, 14), // "Wifi_Read_Data"
QT_MOC_LITERAL(11, 132, 14), // "socket_Connect"
QT_MOC_LITERAL(12, 147, 9), // "TCP_COMM*"
QT_MOC_LITERAL(13, 157, 8), // "tcp_comm"
QT_MOC_LITERAL(14, 166, 11), // "socket_init"
QT_MOC_LITERAL(15, 178, 11), // "socket_Send"
QT_MOC_LITERAL(16, 190, 9), // "send_data"
QT_MOC_LITERAL(17, 200, 8), // "uint32_t"
QT_MOC_LITERAL(18, 209, 3), // "len"
QT_MOC_LITERAL(19, 213, 12), // "socket_Close"
QT_MOC_LITERAL(20, 226, 17), // "socket1_Connected"
QT_MOC_LITERAL(21, 244, 17), // "socket2_Connected"
QT_MOC_LITERAL(22, 262, 17), // "socket3_Connected"
QT_MOC_LITERAL(23, 280, 17), // "socket4_Connected"
QT_MOC_LITERAL(24, 298, 17), // "socket5_Connected"
QT_MOC_LITERAL(25, 316, 20), // "socket1_Disconnected"
QT_MOC_LITERAL(26, 337, 20), // "socket2_Disconnected"
QT_MOC_LITERAL(27, 358, 20), // "socket3_Disconnected"
QT_MOC_LITERAL(28, 379, 20), // "socket4_Disconnected"
QT_MOC_LITERAL(29, 400, 20), // "socket5_Disconnected"
QT_MOC_LITERAL(30, 421, 17), // "socket1_Read_Data"
QT_MOC_LITERAL(31, 439, 17), // "socket2_Read_Data"
QT_MOC_LITERAL(32, 457, 17), // "socket3_Read_Data"
QT_MOC_LITERAL(33, 475, 17), // "socket4_Read_Data"
QT_MOC_LITERAL(34, 493, 17), // "socket5_Read_Data"
QT_MOC_LITERAL(35, 511, 15), // "socket_comm_fun"
QT_MOC_LITERAL(36, 527, 10), // "floatToBCD"
QT_MOC_LITERAL(37, 538, 6), // "number"
QT_MOC_LITERAL(38, 545, 10), // "queryTable"
QT_MOC_LITERAL(39, 556, 9), // "tableName"
QT_MOC_LITERAL(40, 566, 14), // "cleanupOldData"
QT_MOC_LITERAL(41, 581, 14), // "query_oneTable"
QT_MOC_LITERAL(42, 596, 10), // "DATA_BASE2"
QT_MOC_LITERAL(43, 607, 9), // "data_time"
QT_MOC_LITERAL(44, 617, 16), // "singleInsertData"
QT_MOC_LITERAL(45, 634, 10), // "table_name"
QT_MOC_LITERAL(46, 645, 11), // "DATA_BASE2&"
QT_MOC_LITERAL(47, 657, 10), // "singleData"
QT_MOC_LITERAL(48, 668, 8), // "alarmTXT"
QT_MOC_LITERAL(49, 677, 14), // "moreInsertData"
QT_MOC_LITERAL(50, 692, 18), // "QList<DATA_BASE2>&"
QT_MOC_LITERAL(51, 711, 8), // "moreData"
QT_MOC_LITERAL(52, 720, 10), // "modifyData"
QT_MOC_LITERAL(53, 731, 2), // "db"
QT_MOC_LITERAL(54, 734, 13), // "deleteAllData"
QT_MOC_LITERAL(55, 748, 20), // "delete_AllData_Total"
QT_MOC_LITERAL(56, 769, 23), // "delete_ReSendData_Total"
QT_MOC_LITERAL(57, 793, 10), // "deleteData"
QT_MOC_LITERAL(58, 804, 2), // "id"
QT_MOC_LITERAL(59, 807, 11), // "deleteTable"
QT_MOC_LITERAL(60, 819, 16), // "reSendInsertData"
QT_MOC_LITERAL(61, 836, 6), // "tcpNum"
QT_MOC_LITERAL(62, 843, 4), // "mark"
QT_MOC_LITERAL(63, 848, 4), // "data"
QT_MOC_LITERAL(64, 853, 11), // "reSendQuery"
QT_MOC_LITERAL(65, 865, 12), // "reSendDelete"
QT_MOC_LITERAL(66, 878, 16), // "reSendQueryPoint"
QT_MOC_LITERAL(67, 895, 17), // "reSendDeletePoint"
QT_MOC_LITERAL(68, 913, 20), // "reSendInsertData_SZY"
QT_MOC_LITERAL(69, 934, 5), // "count"
QT_MOC_LITERAL(70, 940, 15), // "reSendQuery_SZY"
QT_MOC_LITERAL(71, 956, 3), // "num"
QT_MOC_LITERAL(72, 960, 16), // "reSendDelete_SZY"
QT_MOC_LITERAL(73, 977, 20), // "reSendQueryPoint_SZY"
QT_MOC_LITERAL(74, 998, 21), // "reSendDeletePoint_SZY"
QT_MOC_LITERAL(75, 1020, 24), // "timerTimeout_SZY_resend1"
QT_MOC_LITERAL(76, 1045, 24), // "timerTimeout_SZY_resend2"
QT_MOC_LITERAL(77, 1070, 24), // "timerTimeout_SZY_resend3"
QT_MOC_LITERAL(78, 1095, 24), // "timerTimeout_SZY_resend4"
QT_MOC_LITERAL(79, 1120, 19), // "report_SW_head_init"
QT_MOC_LITERAL(80, 1140, 20), // "report_SZY_head_init"
QT_MOC_LITERAL(81, 1161, 19), // "timerTimeout_second"
QT_MOC_LITERAL(82, 1181, 22), // "Timeout_second_picture"
QT_MOC_LITERAL(83, 1204, 29), // "Timeout_send_maintenance_file"
QT_MOC_LITERAL(84, 1234, 19), // "timerTimeout_minute"
QT_MOC_LITERAL(85, 1254, 16), // "maintenance_link"
QT_MOC_LITERAL(86, 1271, 20), // "Factory_Config_Reset"
QT_MOC_LITERAL(87, 1292, 8), // "Tcp_comm"
QT_MOC_LITERAL(88, 1301, 16), // "Store_Data_Reset"
QT_MOC_LITERAL(89, 1318, 10), // "check_time"
QT_MOC_LITERAL(90, 1329, 17), // "report_fixed_time"
QT_MOC_LITERAL(91, 1347, 16), // "socket_agreement"
QT_MOC_LITERAL(92, 1364, 14), // "report_SW_link"
QT_MOC_LITERAL(93, 1379, 14), // "report_SW_test"
QT_MOC_LITERAL(94, 1394, 22), // "report_SW_uniform_time"
QT_MOC_LITERAL(95, 1417, 8), // "fun_code"
QT_MOC_LITERAL(96, 1426, 4), // "type"
QT_MOC_LITERAL(97, 1431, 20), // "report_SW_fixed_time"
QT_MOC_LITERAL(98, 1452, 13), // "report_SW_add"
QT_MOC_LITERAL(99, 1466, 14), // "report_SW_hour"
QT_MOC_LITERAL(100, 1481, 21), // "report_SW_Manual_Work"
QT_MOC_LITERAL(101, 1503, 22), // "report_SW_fixedPicture"
QT_MOC_LITERAL(102, 1526, 7), // "dir_pic"
QT_MOC_LITERAL(103, 1534, 28), // "report_SW_Ask_Water_PumpPara"
QT_MOC_LITERAL(104, 1563, 21), // "report_SW_Set_ICstate"
QT_MOC_LITERAL(105, 1585, 5), // "state"
QT_MOC_LITERAL(106, 1591, 29), // "report_SW_Set_Water_Pumpstate"
QT_MOC_LITERAL(107, 1621, 8), // "uint16_t"
QT_MOC_LITERAL(108, 1630, 24), // "report_SW_Set_Valvestate"
QT_MOC_LITERAL(109, 1655, 23), // "report_SW_Set_gatestate"
QT_MOC_LITERAL(110, 1679, 5), // "value"
QT_MOC_LITERAL(111, 1685, 26), // "report_SW_Set_Watersetting"
QT_MOC_LITERAL(112, 1712, 22), // "report_SW_QueryVersion"
QT_MOC_LITERAL(113, 1735, 22), // "report_SW_Set_Password"
QT_MOC_LITERAL(114, 1758, 27), // "report_SW_Query_stationTime"
QT_MOC_LITERAL(115, 1786, 28), // "report_SW_QueryRealTime_Data"
QT_MOC_LITERAL(116, 1815, 27), // "report_SW_QueryUniform_Time"
QT_MOC_LITERAL(117, 1843, 5), // "time1"
QT_MOC_LITERAL(118, 1849, 5), // "time2"
QT_MOC_LITERAL(119, 1855, 26), // "report_SW_QueryManual_Work"
QT_MOC_LITERAL(120, 1882, 21), // "report_SW_Query_Alarm"
QT_MOC_LITERAL(121, 1904, 21), // "report_SW_Query_Event"
QT_MOC_LITERAL(122, 1926, 31), // "report_SW_Query_APPOINT_ELEMENT"
QT_MOC_LITERAL(123, 1958, 19), // "report_SW_Set_Clock"
QT_MOC_LITERAL(124, 1978, 26), // "report_SW_Modify_Basic_Set"
QT_MOC_LITERAL(125, 2005, 25), // "report_SW_Query_Basic_Set"
QT_MOC_LITERAL(126, 2031, 24), // "report_SW_Modify_Run_Set"
QT_MOC_LITERAL(127, 2056, 23), // "report_SW_Query_Run_Set"
QT_MOC_LITERAL(128, 2080, 17), // "report_SW_picture"
QT_MOC_LITERAL(129, 2098, 15), // "report_SZY_link"
QT_MOC_LITERAL(130, 2114, 24), // "report_SZY_SetWaterLevel"
QT_MOC_LITERAL(131, 2139, 26), // "report_SZY_QueryWaterLevel"
QT_MOC_LITERAL(132, 2166, 18), // "report_SZY_SetFlow"
QT_MOC_LITERAL(133, 2185, 20), // "report_SZY_QueryFlow"
QT_MOC_LITERAL(134, 2206, 19), // "report_SZY_SetClock"
QT_MOC_LITERAL(135, 2226, 21), // "report_SZY_QueryClock"
QT_MOC_LITERAL(136, 2248, 22), // "report_SZY_SetWorkMode"
QT_MOC_LITERAL(137, 2271, 24), // "report_SZY_QueryWorkMode"
QT_MOC_LITERAL(138, 2296, 21), // "report_SZY_SetAddress"
QT_MOC_LITERAL(139, 2318, 23), // "report_SZY_QueryAddress"
QT_MOC_LITERAL(140, 2342, 22), // "report_SZY_SetPassword"
QT_MOC_LITERAL(141, 2365, 26), // "report_SZY_QueryUploadTime"
QT_MOC_LITERAL(142, 2392, 24), // "report_SZY_SetUploadTime"
QT_MOC_LITERAL(143, 2417, 24), // "report_SZY_QueryAllState"
QT_MOC_LITERAL(144, 2442, 24), // "report_SZY_ResetTerminal"
QT_MOC_LITERAL(145, 2467, 28), // "report_SZY_DeleteHistoryData"
QT_MOC_LITERAL(146, 2496, 18), // "report_SZY_OpenKDY"
QT_MOC_LITERAL(147, 2515, 19), // "report_SZY_CloseKDY"
QT_MOC_LITERAL(148, 2535, 32), // "report_SZY_SetThresholdStoreTime"
QT_MOC_LITERAL(149, 2568, 29), // "report_SZY_QueryRealTimeValue"
QT_MOC_LITERAL(150, 2598, 20), // "report_SZY_QueryData"
QT_MOC_LITERAL(151, 2619, 26), // "report_SZY_QueryUploadData"
QT_MOC_LITERAL(152, 2646, 23), // "report_SZY_QueryPicture"
QT_MOC_LITERAL(153, 2670, 19), // "report_SZY_EnableIC"
QT_MOC_LITERAL(154, 2690, 20), // "report_SZY_DisableIC"
QT_MOC_LITERAL(155, 2711, 21), // "report_SZY_fixed_time"
QT_MOC_LITERAL(156, 2733, 10), // "camera_fun"
QT_MOC_LITERAL(157, 2744, 9), // "camera_ip"
QT_MOC_LITERAL(158, 2754, 11), // "camera_name"
QT_MOC_LITERAL(159, 2766, 15), // "camera_password"
QT_MOC_LITERAL(160, 2782, 14), // "report_pwCheck"
QT_MOC_LITERAL(161, 2797, 5), // "array"
QT_MOC_LITERAL(162, 2803, 5), // "index"
QT_MOC_LITERAL(163, 2809, 20), // "timerTimeout_receive"
QT_MOC_LITERAL(164, 2830, 11), // "ModBusCRC16"
QT_MOC_LITERAL(165, 2842, 8), // "CRC8_SZY"
QT_MOC_LITERAL(166, 2851, 6), // "buffer"
QT_MOC_LITERAL(167, 2858, 7), // "cLength"
QT_MOC_LITERAL(168, 2866, 22), // "serial_send_disconnect"
QT_MOC_LITERAL(169, 2889, 10), // "uwordToBcd"
QT_MOC_LITERAL(170, 2900, 9), // "wordToBcd"
QT_MOC_LITERAL(171, 2910, 7), // "int32_t"
QT_MOC_LITERAL(172, 2918, 10), // "wordTo3Bcd"
QT_MOC_LITERAL(173, 2929, 11), // "uwordTo3Bcd"
QT_MOC_LITERAL(174, 2941, 12), // "udwordToDBcd"
QT_MOC_LITERAL(175, 2954, 8), // "uint64_t"
QT_MOC_LITERAL(176, 2963, 9), // "byteToBcd"
QT_MOC_LITERAL(177, 2973, 9), // "BCDtobyte"
QT_MOC_LITERAL(178, 2983, 3), // "bcd"
QT_MOC_LITERAL(179, 2987, 13), // "BCDtoHalfword"
QT_MOC_LITERAL(180, 3001, 9), // "bcdToWord"
QT_MOC_LITERAL(181, 3011, 9), // "plusMinus"
QT_MOC_LITERAL(182, 3021, 10), // "bcdToUword"
QT_MOC_LITERAL(183, 3032, 10), // "Delay_MSec"
QT_MOC_LITERAL(184, 3043, 4), // "msec"
QT_MOC_LITERAL(185, 3048, 15), // "convertHexChart"
QT_MOC_LITERAL(186, 3064, 2), // "ch"
QT_MOC_LITERAL(187, 3067, 11), // "StringToHex"
QT_MOC_LITERAL(188, 3079, 3), // "str"
QT_MOC_LITERAL(189, 3083, 11), // "QByteArray&"
QT_MOC_LITERAL(190, 3095, 8) // "senddata"

    },
    "tcp_socket\0uploadTime\0\0uint8_t\0"
    "uploadPassword\0kdy_signal\0uploadBaseSet\0"
    "uploadRunSet\0Wifi_Connected\0"
    "Wifi_Disconnected\0Wifi_Read_Data\0"
    "socket_Connect\0TCP_COMM*\0tcp_comm\0"
    "socket_init\0socket_Send\0send_data\0"
    "uint32_t\0len\0socket_Close\0socket1_Connected\0"
    "socket2_Connected\0socket3_Connected\0"
    "socket4_Connected\0socket5_Connected\0"
    "socket1_Disconnected\0socket2_Disconnected\0"
    "socket3_Disconnected\0socket4_Disconnected\0"
    "socket5_Disconnected\0socket1_Read_Data\0"
    "socket2_Read_Data\0socket3_Read_Data\0"
    "socket4_Read_Data\0socket5_Read_Data\0"
    "socket_comm_fun\0floatToBCD\0number\0"
    "queryTable\0tableName\0cleanupOldData\0"
    "query_oneTable\0DATA_BASE2\0data_time\0"
    "singleInsertData\0table_name\0DATA_BASE2&\0"
    "singleData\0alarmTXT\0moreInsertData\0"
    "QList<DATA_BASE2>&\0moreData\0modifyData\0"
    "db\0deleteAllData\0delete_AllData_Total\0"
    "delete_ReSendData_Total\0deleteData\0"
    "id\0deleteTable\0reSendInsertData\0tcpNum\0"
    "mark\0data\0reSendQuery\0reSendDelete\0"
    "reSendQueryPoint\0reSendDeletePoint\0"
    "reSendInsertData_SZY\0count\0reSendQuery_SZY\0"
    "num\0reSendDelete_SZY\0reSendQueryPoint_SZY\0"
    "reSendDeletePoint_SZY\0timerTimeout_SZY_resend1\0"
    "timerTimeout_SZY_resend2\0"
    "timerTimeout_SZY_resend3\0"
    "timerTimeout_SZY_resend4\0report_SW_head_init\0"
    "report_SZY_head_init\0timerTimeout_second\0"
    "Timeout_second_picture\0"
    "Timeout_send_maintenance_file\0"
    "timerTimeout_minute\0maintenance_link\0"
    "Factory_Config_Reset\0Tcp_comm\0"
    "Store_Data_Reset\0check_time\0"
    "report_fixed_time\0socket_agreement\0"
    "report_SW_link\0report_SW_test\0"
    "report_SW_uniform_time\0fun_code\0type\0"
    "report_SW_fixed_time\0report_SW_add\0"
    "report_SW_hour\0report_SW_Manual_Work\0"
    "report_SW_fixedPicture\0dir_pic\0"
    "report_SW_Ask_Water_PumpPara\0"
    "report_SW_Set_ICstate\0state\0"
    "report_SW_Set_Water_Pumpstate\0uint16_t\0"
    "report_SW_Set_Valvestate\0"
    "report_SW_Set_gatestate\0value\0"
    "report_SW_Set_Watersetting\0"
    "report_SW_QueryVersion\0report_SW_Set_Password\0"
    "report_SW_Query_stationTime\0"
    "report_SW_QueryRealTime_Data\0"
    "report_SW_QueryUniform_Time\0time1\0"
    "time2\0report_SW_QueryManual_Work\0"
    "report_SW_Query_Alarm\0report_SW_Query_Event\0"
    "report_SW_Query_APPOINT_ELEMENT\0"
    "report_SW_Set_Clock\0report_SW_Modify_Basic_Set\0"
    "report_SW_Query_Basic_Set\0"
    "report_SW_Modify_Run_Set\0"
    "report_SW_Query_Run_Set\0report_SW_picture\0"
    "report_SZY_link\0report_SZY_SetWaterLevel\0"
    "report_SZY_QueryWaterLevel\0"
    "report_SZY_SetFlow\0report_SZY_QueryFlow\0"
    "report_SZY_SetClock\0report_SZY_QueryClock\0"
    "report_SZY_SetWorkMode\0report_SZY_QueryWorkMode\0"
    "report_SZY_SetAddress\0report_SZY_QueryAddress\0"
    "report_SZY_SetPassword\0"
    "report_SZY_QueryUploadTime\0"
    "report_SZY_SetUploadTime\0"
    "report_SZY_QueryAllState\0"
    "report_SZY_ResetTerminal\0"
    "report_SZY_DeleteHistoryData\0"
    "report_SZY_OpenKDY\0report_SZY_CloseKDY\0"
    "report_SZY_SetThresholdStoreTime\0"
    "report_SZY_QueryRealTimeValue\0"
    "report_SZY_QueryData\0report_SZY_QueryUploadData\0"
    "report_SZY_QueryPicture\0report_SZY_EnableIC\0"
    "report_SZY_DisableIC\0report_SZY_fixed_time\0"
    "camera_fun\0camera_ip\0camera_name\0"
    "camera_password\0report_pwCheck\0array\0"
    "index\0timerTimeout_receive\0ModBusCRC16\0"
    "CRC8_SZY\0buffer\0cLength\0serial_send_disconnect\0"
    "uwordToBcd\0wordToBcd\0int32_t\0wordTo3Bcd\0"
    "uwordTo3Bcd\0udwordToDBcd\0uint64_t\0"
    "byteToBcd\0BCDtobyte\0bcd\0BCDtoHalfword\0"
    "bcdToWord\0plusMinus\0bcdToUword\0"
    "Delay_MSec\0msec\0convertHexChart\0ch\0"
    "StringToHex\0str\0QByteArray&\0senddata"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_tcp_socket[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
     141,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       5,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,  719,    2, 0x06 /* Public */,
       4,    1,  722,    2, 0x06 /* Public */,
       5,    1,  725,    2, 0x06 /* Public */,
       6,    1,  728,    2, 0x06 /* Public */,
       7,    1,  731,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       8,    0,  734,    2, 0x0a /* Public */,
       9,    0,  735,    2, 0x0a /* Public */,
      10,    0,  736,    2, 0x0a /* Public */,
      11,    1,  737,    2, 0x0a /* Public */,
      14,    0,  740,    2, 0x0a /* Public */,
      15,    3,  741,    2, 0x0a /* Public */,
      19,    1,  748,    2, 0x0a /* Public */,
      20,    0,  751,    2, 0x0a /* Public */,
      21,    0,  752,    2, 0x0a /* Public */,
      22,    0,  753,    2, 0x0a /* Public */,
      23,    0,  754,    2, 0x0a /* Public */,
      24,    0,  755,    2, 0x0a /* Public */,
      25,    0,  756,    2, 0x0a /* Public */,
      26,    0,  757,    2, 0x0a /* Public */,
      27,    0,  758,    2, 0x0a /* Public */,
      28,    0,  759,    2, 0x0a /* Public */,
      29,    0,  760,    2, 0x0a /* Public */,
      30,    0,  761,    2, 0x0a /* Public */,
      31,    0,  762,    2, 0x0a /* Public */,
      32,    0,  763,    2, 0x0a /* Public */,
      33,    0,  764,    2, 0x0a /* Public */,
      34,    0,  765,    2, 0x0a /* Public */,
      35,    1,  766,    2, 0x0a /* Public */,
      36,    1,  769,    2, 0x0a /* Public */,
      38,    1,  772,    2, 0x0a /* Public */,
      40,    0,  775,    2, 0x0a /* Public */,
      41,    2,  776,    2, 0x0a /* Public */,
      44,    3,  781,    2, 0x0a /* Public */,
      49,    2,  788,    2, 0x0a /* Public */,
      52,    2,  793,    2, 0x0a /* Public */,
      54,    1,  798,    2, 0x0a /* Public */,
      55,    0,  801,    2, 0x0a /* Public */,
      56,    0,  802,    2, 0x0a /* Public */,
      57,    2,  803,    2, 0x0a /* Public */,
      59,    1,  808,    2, 0x0a /* Public */,
      60,    3,  811,    2, 0x0a /* Public */,
      64,    1,  818,    2, 0x0a /* Public */,
      65,    1,  821,    2, 0x0a /* Public */,
      66,    2,  824,    2, 0x0a /* Public */,
      67,    2,  829,    2, 0x0a /* Public */,
      68,    4,  834,    2, 0x0a /* Public */,
      70,    2,  843,    2, 0x0a /* Public */,
      72,    1,  848,    2, 0x0a /* Public */,
      73,    2,  851,    2, 0x0a /* Public */,
      74,    2,  856,    2, 0x0a /* Public */,
      75,    0,  861,    2, 0x0a /* Public */,
      76,    0,  862,    2, 0x0a /* Public */,
      77,    0,  863,    2, 0x0a /* Public */,
      78,    0,  864,    2, 0x0a /* Public */,
      79,    0,  865,    2, 0x08 /* Private */,
      80,    0,  866,    2, 0x08 /* Private */,
      81,    0,  867,    2, 0x08 /* Private */,
      82,    0,  868,    2, 0x08 /* Private */,
      83,    0,  869,    2, 0x08 /* Private */,
      84,    0,  870,    2, 0x08 /* Private */,
      85,    0,  871,    2, 0x08 /* Private */,
      86,    1,  872,    2, 0x08 /* Private */,
      88,    1,  875,    2, 0x08 /* Private */,
      89,    1,  878,    2, 0x08 /* Private */,
      90,    1,  881,    2, 0x08 /* Private */,
      92,    1,  884,    2, 0x08 /* Private */,
      92,    0,  887,    2, 0x08 /* Private */,
      93,    0,  888,    2, 0x08 /* Private */,
      94,    2,  889,    2, 0x08 /* Private */,
      97,    1,  894,    2, 0x08 /* Private */,
      98,    0,  897,    2, 0x08 /* Private */,
      99,    0,  898,    2, 0x08 /* Private */,
     100,    0,  899,    2, 0x08 /* Private */,
     101,    1,  900,    2, 0x08 /* Private */,
     103,    1,  903,    2, 0x08 /* Private */,
     104,    2,  906,    2, 0x08 /* Private */,
     106,    2,  911,    2, 0x08 /* Private */,
     108,    2,  916,    2, 0x08 /* Private */,
     109,    3,  921,    2, 0x08 /* Private */,
     111,    2,  928,    2, 0x08 /* Private */,
     112,    1,  933,    2, 0x08 /* Private */,
     113,    1,  936,    2, 0x08 /* Private */,
     114,    1,  939,    2, 0x08 /* Private */,
     115,    1,  942,    2, 0x08 /* Private */,
     116,    4,  945,    2, 0x08 /* Private */,
     119,    1,  954,    2, 0x08 /* Private */,
     120,    1,  957,    2, 0x08 /* Private */,
     121,    1,  960,    2, 0x08 /* Private */,
     122,    1,  963,    2, 0x08 /* Private */,
     123,    1,  966,    2, 0x08 /* Private */,
     124,    1,  969,    2, 0x08 /* Private */,
     125,    1,  972,    2, 0x08 /* Private */,
     126,    1,  975,    2, 0x08 /* Private */,
     127,    1,  978,    2, 0x08 /* Private */,
     128,    2,  981,    2, 0x08 /* Private */,
     129,    2,  986,    2, 0x08 /* Private */,
     130,    1,  991,    2, 0x08 /* Private */,
     131,    1,  994,    2, 0x08 /* Private */,
     132,    1,  997,    2, 0x08 /* Private */,
     133,    1, 1000,    2, 0x08 /* Private */,
     134,    1, 1003,    2, 0x08 /* Private */,
     135,    1, 1006,    2, 0x08 /* Private */,
     136,    1, 1009,    2, 0x08 /* Private */,
     137,    1, 1012,    2, 0x08 /* Private */,
     138,    1, 1015,    2, 0x08 /* Private */,
     139,    1, 1018,    2, 0x08 /* Private */,
     140,    1, 1021,    2, 0x08 /* Private */,
     141,    1, 1024,    2, 0x08 /* Private */,
     142,    1, 1027,    2, 0x08 /* Private */,
     143,    1, 1030,    2, 0x08 /* Private */,
     144,    1, 1033,    2, 0x08 /* Private */,
     145,    1, 1036,    2, 0x08 /* Private */,
     146,    1, 1039,    2, 0x08 /* Private */,
     147,    1, 1042,    2, 0x08 /* Private */,
     148,    1, 1045,    2, 0x08 /* Private */,
     149,    1, 1048,    2, 0x08 /* Private */,
     150,    1, 1051,    2, 0x08 /* Private */,
     151,    1, 1054,    2, 0x08 /* Private */,
     152,    2, 1057,    2, 0x08 /* Private */,
     153,    1, 1062,    2, 0x08 /* Private */,
     154,    1, 1065,    2, 0x08 /* Private */,
     155,    1, 1068,    2, 0x08 /* Private */,
     156,    3, 1071,    2, 0x08 /* Private */,
     160,    2, 1078,    2, 0x08 /* Private */,
     163,    0, 1083,    2, 0x08 /* Private */,
     164,    2, 1084,    2, 0x08 /* Private */,
     165,    2, 1089,    2, 0x08 /* Private */,
     168,    0, 1094,    2, 0x08 /* Private */,
     169,    1, 1095,    2, 0x08 /* Private */,
     170,    1, 1098,    2, 0x08 /* Private */,
     172,    1, 1101,    2, 0x08 /* Private */,
     173,    1, 1104,    2, 0x08 /* Private */,
     174,    1, 1107,    2, 0x08 /* Private */,
     176,    1, 1110,    2, 0x08 /* Private */,
     177,    1, 1113,    2, 0x08 /* Private */,
     179,    1, 1116,    2, 0x08 /* Private */,
     180,    4, 1119,    2, 0x08 /* Private */,
     182,    3, 1128,    2, 0x08 /* Private */,
     183,    1, 1135,    2, 0x08 /* Private */,
     185,    1, 1138,    2, 0x08 /* Private */,
     187,    2, 1141,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3,    2,
    QMetaType::Void, QMetaType::QString,    2,
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void, QMetaType::Int,    2,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 12,   13,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 12, QMetaType::QByteArray, 0x80000000 | 17,   13,   16,   18,
    QMetaType::Void, 0x80000000 | 12,   13,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 12,   13,
    QMetaType::QString, QMetaType::Float,   37,
    QMetaType::Void, QMetaType::QString,   39,
    QMetaType::Void,
    0x80000000 | 42, QMetaType::QString, QMetaType::QString,   39,   43,
    QMetaType::Void, QMetaType::QString, 0x80000000 | 46, QMetaType::QString,   45,   47,   48,
    QMetaType::Void, QMetaType::QString, 0x80000000 | 50,   39,   51,
    QMetaType::Void, QMetaType::QString, 0x80000000 | 42,   39,   53,
    QMetaType::Void, QMetaType::QString,   39,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString, QMetaType::Int,   39,   58,
    QMetaType::Void, QMetaType::QString,   39,
    QMetaType::Void, 0x80000000 | 3, QMetaType::QString, QMetaType::QString,   61,   62,   63,
    QMetaType::Bool, 0x80000000 | 3,   61,
    QMetaType::Void, 0x80000000 | 3,   61,
    QMetaType::Bool, 0x80000000 | 3, QMetaType::QString,   61,   62,
    QMetaType::Void, 0x80000000 | 3, QMetaType::QString,   61,   62,
    QMetaType::Void, 0x80000000 | 3, QMetaType::QString, 0x80000000 | 3, QMetaType::QString,   61,   62,   69,   63,
    QMetaType::Bool, 0x80000000 | 3, 0x80000000 | 3,   61,   71,
    QMetaType::Void, 0x80000000 | 3,   61,
    QMetaType::Bool, 0x80000000 | 3, QMetaType::QString,   61,   62,
    QMetaType::Void, 0x80000000 | 3, QMetaType::QString,   61,   62,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 12,   87,
    QMetaType::Void, 0x80000000 | 12,   87,
    QMetaType::Void, 0x80000000 | 12,   87,
    QMetaType::Void, 0x80000000 | 3,   91,
    QMetaType::Void, 0x80000000 | 12,   87,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 3, 0x80000000 | 3,   95,   96,
    QMetaType::Void, 0x80000000 | 3,   95,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,  102,
    QMetaType::Void, 0x80000000 | 12,   87,
    QMetaType::Void, 0x80000000 | 12, 0x80000000 | 17,   87,  105,
    QMetaType::Void, 0x80000000 | 12, 0x80000000 | 107,   87,  105,
    QMetaType::Void, 0x80000000 | 12, 0x80000000 | 107,   87,  105,
    QMetaType::Void, 0x80000000 | 12, 0x80000000 | 17, 0x80000000 | 107,   87,  105,  110,
    QMetaType::Void, 0x80000000 | 12, 0x80000000 | 3,   87,  105,
    QMetaType::Void, 0x80000000 | 12,   87,
    QMetaType::Void, 0x80000000 | 12,   87,
    QMetaType::Void, 0x80000000 | 12,   87,
    QMetaType::Void, 0x80000000 | 12,   87,
    QMetaType::Void, 0x80000000 | 12, 0x80000000 | 3, QMetaType::QString, QMetaType::QString,   87,   96,  117,  118,
    QMetaType::Void, 0x80000000 | 12,   87,
    QMetaType::Void, 0x80000000 | 12,   87,
    QMetaType::Void, 0x80000000 | 12,   87,
    QMetaType::Void, 0x80000000 | 12,   87,
    QMetaType::Void, 0x80000000 | 12,   87,
    QMetaType::Void, 0x80000000 | 12,   87,
    QMetaType::Void, 0x80000000 | 12,   87,
    QMetaType::Void, 0x80000000 | 12,   87,
    QMetaType::Void, 0x80000000 | 12,   87,
    QMetaType::Void, 0x80000000 | 12, QMetaType::QString,   87,  102,
    QMetaType::Void, 0x80000000 | 12, 0x80000000 | 3,   13,   95,
    QMetaType::Void, 0x80000000 | 12,   13,
    QMetaType::Void, 0x80000000 | 12,   13,
    QMetaType::Void, 0x80000000 | 12,   13,
    QMetaType::Void, 0x80000000 | 12,   13,
    QMetaType::Void, 0x80000000 | 12,   13,
    QMetaType::Void, 0x80000000 | 12,   13,
    QMetaType::Void, 0x80000000 | 12,   13,
    QMetaType::Void, 0x80000000 | 12,   13,
    QMetaType::Void, 0x80000000 | 12,   13,
    QMetaType::Void, 0x80000000 | 12,   13,
    QMetaType::Void, 0x80000000 | 12,   13,
    QMetaType::Void, 0x80000000 | 12,   13,
    QMetaType::Void, 0x80000000 | 12,   13,
    QMetaType::Void, 0x80000000 | 12,   13,
    QMetaType::Void, 0x80000000 | 12,   13,
    QMetaType::Void, 0x80000000 | 12,   13,
    QMetaType::Void, 0x80000000 | 12,   13,
    QMetaType::Void, 0x80000000 | 12,   13,
    QMetaType::Void, 0x80000000 | 12,   13,
    QMetaType::Void, 0x80000000 | 12,   13,
    QMetaType::Void, 0x80000000 | 12,   13,
    QMetaType::Void, 0x80000000 | 12,   13,
    QMetaType::Void, 0x80000000 | 12, QMetaType::QString,   13,  102,
    QMetaType::Void, 0x80000000 | 12,   13,
    QMetaType::Void, 0x80000000 | 12,   13,
    QMetaType::Void, 0x80000000 | 3,   95,
    QMetaType::QString, QMetaType::QString, QMetaType::QString, QMetaType::QString,  157,  158,  159,
    QMetaType::Bool, QMetaType::QByteArray, 0x80000000 | 17,  161,  162,
    QMetaType::Void,
    0x80000000 | 107, QMetaType::QByteArray, 0x80000000 | 17,   63,   18,
    0x80000000 | 3, QMetaType::QByteArray, 0x80000000 | 107,  166,  167,
    QMetaType::Void,
    0x80000000 | 17, 0x80000000 | 17,  110,
    0x80000000 | 17, 0x80000000 | 171,  110,
    0x80000000 | 17, 0x80000000 | 171,  110,
    0x80000000 | 17, 0x80000000 | 17,  110,
    0x80000000 | 175, 0x80000000 | 175,  110,
    0x80000000 | 3, 0x80000000 | 3,  110,
    0x80000000 | 3, 0x80000000 | 3,  178,
    0x80000000 | 107, 0x80000000 | 107,  178,
    0x80000000 | 171, QMetaType::QByteArray, 0x80000000 | 17, 0x80000000 | 3, QMetaType::Bool,  161,  162,   18,  181,
    0x80000000 | 17, QMetaType::QByteArray, 0x80000000 | 17, 0x80000000 | 3,  161,  162,   18,
    QMetaType::Void, QMetaType::UInt,  184,
    QMetaType::Char, QMetaType::Char,  186,
    QMetaType::Void, QMetaType::QString, 0x80000000 | 189,  188,  190,

       0        // eod
};

void tcp_socket::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<tcp_socket *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->uploadTime((*reinterpret_cast< uint8_t(*)>(_a[1]))); break;
        case 1: _t->uploadPassword((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 2: _t->kdy_signal((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 3: _t->uploadBaseSet((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 4: _t->uploadRunSet((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 5: _t->Wifi_Connected(); break;
        case 6: _t->Wifi_Disconnected(); break;
        case 7: _t->Wifi_Read_Data(); break;
        case 8: _t->socket_Connect((*reinterpret_cast< TCP_COMM*(*)>(_a[1]))); break;
        case 9: _t->socket_init(); break;
        case 10: _t->socket_Send((*reinterpret_cast< TCP_COMM*(*)>(_a[1])),(*reinterpret_cast< QByteArray(*)>(_a[2])),(*reinterpret_cast< uint32_t(*)>(_a[3]))); break;
        case 11: _t->socket_Close((*reinterpret_cast< TCP_COMM*(*)>(_a[1]))); break;
        case 12: _t->socket1_Connected(); break;
        case 13: _t->socket2_Connected(); break;
        case 14: _t->socket3_Connected(); break;
        case 15: _t->socket4_Connected(); break;
        case 16: _t->socket5_Connected(); break;
        case 17: _t->socket1_Disconnected(); break;
        case 18: _t->socket2_Disconnected(); break;
        case 19: _t->socket3_Disconnected(); break;
        case 20: _t->socket4_Disconnected(); break;
        case 21: _t->socket5_Disconnected(); break;
        case 22: _t->socket1_Read_Data(); break;
        case 23: _t->socket2_Read_Data(); break;
        case 24: _t->socket3_Read_Data(); break;
        case 25: _t->socket4_Read_Data(); break;
        case 26: _t->socket5_Read_Data(); break;
        case 27: _t->socket_comm_fun((*reinterpret_cast< TCP_COMM*(*)>(_a[1]))); break;
        case 28: { QString _r = _t->floatToBCD((*reinterpret_cast< float(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 29: _t->queryTable((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 30: _t->cleanupOldData(); break;
        case 31: { DATA_BASE2 _r = _t->query_oneTable((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< DATA_BASE2*>(_a[0]) = std::move(_r); }  break;
        case 32: _t->singleInsertData((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< DATA_BASE2(*)>(_a[2])),(*reinterpret_cast< QString(*)>(_a[3]))); break;
        case 33: _t->moreInsertData((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QList<DATA_BASE2>(*)>(_a[2]))); break;
        case 34: _t->modifyData((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< DATA_BASE2(*)>(_a[2]))); break;
        case 35: _t->deleteAllData((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 36: _t->delete_AllData_Total(); break;
        case 37: _t->delete_ReSendData_Total(); break;
        case 38: _t->deleteData((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 39: _t->deleteTable((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 40: _t->reSendInsertData((*reinterpret_cast< uint8_t(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])),(*reinterpret_cast< QString(*)>(_a[3]))); break;
        case 41: { bool _r = _t->reSendQuery((*reinterpret_cast< uint8_t(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 42: _t->reSendDelete((*reinterpret_cast< uint8_t(*)>(_a[1]))); break;
        case 43: { bool _r = _t->reSendQueryPoint((*reinterpret_cast< uint8_t(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 44: _t->reSendDeletePoint((*reinterpret_cast< uint8_t(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 45: _t->reSendInsertData_SZY((*reinterpret_cast< uint8_t(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])),(*reinterpret_cast< uint8_t(*)>(_a[3])),(*reinterpret_cast< QString(*)>(_a[4]))); break;
        case 46: { bool _r = _t->reSendQuery_SZY((*reinterpret_cast< uint8_t(*)>(_a[1])),(*reinterpret_cast< uint8_t(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 47: _t->reSendDelete_SZY((*reinterpret_cast< uint8_t(*)>(_a[1]))); break;
        case 48: { bool _r = _t->reSendQueryPoint_SZY((*reinterpret_cast< uint8_t(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 49: _t->reSendDeletePoint_SZY((*reinterpret_cast< uint8_t(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 50: _t->timerTimeout_SZY_resend1(); break;
        case 51: _t->timerTimeout_SZY_resend2(); break;
        case 52: _t->timerTimeout_SZY_resend3(); break;
        case 53: _t->timerTimeout_SZY_resend4(); break;
        case 54: _t->report_SW_head_init(); break;
        case 55: _t->report_SZY_head_init(); break;
        case 56: _t->timerTimeout_second(); break;
        case 57: _t->Timeout_second_picture(); break;
        case 58: _t->Timeout_send_maintenance_file(); break;
        case 59: _t->timerTimeout_minute(); break;
        case 60: _t->maintenance_link(); break;
        case 61: _t->Factory_Config_Reset((*reinterpret_cast< TCP_COMM*(*)>(_a[1]))); break;
        case 62: _t->Store_Data_Reset((*reinterpret_cast< TCP_COMM*(*)>(_a[1]))); break;
        case 63: _t->check_time((*reinterpret_cast< TCP_COMM*(*)>(_a[1]))); break;
        case 64: _t->report_fixed_time((*reinterpret_cast< uint8_t(*)>(_a[1]))); break;
        case 65: _t->report_SW_link((*reinterpret_cast< TCP_COMM*(*)>(_a[1]))); break;
        case 66: _t->report_SW_link(); break;
        case 67: _t->report_SW_test(); break;
        case 68: _t->report_SW_uniform_time((*reinterpret_cast< uint8_t(*)>(_a[1])),(*reinterpret_cast< uint8_t(*)>(_a[2]))); break;
        case 69: _t->report_SW_fixed_time((*reinterpret_cast< uint8_t(*)>(_a[1]))); break;
        case 70: _t->report_SW_add(); break;
        case 71: _t->report_SW_hour(); break;
        case 72: _t->report_SW_Manual_Work(); break;
        case 73: _t->report_SW_fixedPicture((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 74: _t->report_SW_Ask_Water_PumpPara((*reinterpret_cast< TCP_COMM*(*)>(_a[1]))); break;
        case 75: _t->report_SW_Set_ICstate((*reinterpret_cast< TCP_COMM*(*)>(_a[1])),(*reinterpret_cast< uint32_t(*)>(_a[2]))); break;
        case 76: _t->report_SW_Set_Water_Pumpstate((*reinterpret_cast< TCP_COMM*(*)>(_a[1])),(*reinterpret_cast< uint16_t(*)>(_a[2]))); break;
        case 77: _t->report_SW_Set_Valvestate((*reinterpret_cast< TCP_COMM*(*)>(_a[1])),(*reinterpret_cast< uint16_t(*)>(_a[2]))); break;
        case 78: _t->report_SW_Set_gatestate((*reinterpret_cast< TCP_COMM*(*)>(_a[1])),(*reinterpret_cast< uint32_t(*)>(_a[2])),(*reinterpret_cast< uint16_t(*)>(_a[3]))); break;
        case 79: _t->report_SW_Set_Watersetting((*reinterpret_cast< TCP_COMM*(*)>(_a[1])),(*reinterpret_cast< uint8_t(*)>(_a[2]))); break;
        case 80: _t->report_SW_QueryVersion((*reinterpret_cast< TCP_COMM*(*)>(_a[1]))); break;
        case 81: _t->report_SW_Set_Password((*reinterpret_cast< TCP_COMM*(*)>(_a[1]))); break;
        case 82: _t->report_SW_Query_stationTime((*reinterpret_cast< TCP_COMM*(*)>(_a[1]))); break;
        case 83: _t->report_SW_QueryRealTime_Data((*reinterpret_cast< TCP_COMM*(*)>(_a[1]))); break;
        case 84: _t->report_SW_QueryUniform_Time((*reinterpret_cast< TCP_COMM*(*)>(_a[1])),(*reinterpret_cast< uint8_t(*)>(_a[2])),(*reinterpret_cast< QString(*)>(_a[3])),(*reinterpret_cast< QString(*)>(_a[4]))); break;
        case 85: _t->report_SW_QueryManual_Work((*reinterpret_cast< TCP_COMM*(*)>(_a[1]))); break;
        case 86: _t->report_SW_Query_Alarm((*reinterpret_cast< TCP_COMM*(*)>(_a[1]))); break;
        case 87: _t->report_SW_Query_Event((*reinterpret_cast< TCP_COMM*(*)>(_a[1]))); break;
        case 88: _t->report_SW_Query_APPOINT_ELEMENT((*reinterpret_cast< TCP_COMM*(*)>(_a[1]))); break;
        case 89: _t->report_SW_Set_Clock((*reinterpret_cast< TCP_COMM*(*)>(_a[1]))); break;
        case 90: _t->report_SW_Modify_Basic_Set((*reinterpret_cast< TCP_COMM*(*)>(_a[1]))); break;
        case 91: _t->report_SW_Query_Basic_Set((*reinterpret_cast< TCP_COMM*(*)>(_a[1]))); break;
        case 92: _t->report_SW_Modify_Run_Set((*reinterpret_cast< TCP_COMM*(*)>(_a[1]))); break;
        case 93: _t->report_SW_Query_Run_Set((*reinterpret_cast< TCP_COMM*(*)>(_a[1]))); break;
        case 94: _t->report_SW_picture((*reinterpret_cast< TCP_COMM*(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 95: _t->report_SZY_link((*reinterpret_cast< TCP_COMM*(*)>(_a[1])),(*reinterpret_cast< uint8_t(*)>(_a[2]))); break;
        case 96: _t->report_SZY_SetWaterLevel((*reinterpret_cast< TCP_COMM*(*)>(_a[1]))); break;
        case 97: _t->report_SZY_QueryWaterLevel((*reinterpret_cast< TCP_COMM*(*)>(_a[1]))); break;
        case 98: _t->report_SZY_SetFlow((*reinterpret_cast< TCP_COMM*(*)>(_a[1]))); break;
        case 99: _t->report_SZY_QueryFlow((*reinterpret_cast< TCP_COMM*(*)>(_a[1]))); break;
        case 100: _t->report_SZY_SetClock((*reinterpret_cast< TCP_COMM*(*)>(_a[1]))); break;
        case 101: _t->report_SZY_QueryClock((*reinterpret_cast< TCP_COMM*(*)>(_a[1]))); break;
        case 102: _t->report_SZY_SetWorkMode((*reinterpret_cast< TCP_COMM*(*)>(_a[1]))); break;
        case 103: _t->report_SZY_QueryWorkMode((*reinterpret_cast< TCP_COMM*(*)>(_a[1]))); break;
        case 104: _t->report_SZY_SetAddress((*reinterpret_cast< TCP_COMM*(*)>(_a[1]))); break;
        case 105: _t->report_SZY_QueryAddress((*reinterpret_cast< TCP_COMM*(*)>(_a[1]))); break;
        case 106: _t->report_SZY_SetPassword((*reinterpret_cast< TCP_COMM*(*)>(_a[1]))); break;
        case 107: _t->report_SZY_QueryUploadTime((*reinterpret_cast< TCP_COMM*(*)>(_a[1]))); break;
        case 108: _t->report_SZY_SetUploadTime((*reinterpret_cast< TCP_COMM*(*)>(_a[1]))); break;
        case 109: _t->report_SZY_QueryAllState((*reinterpret_cast< TCP_COMM*(*)>(_a[1]))); break;
        case 110: _t->report_SZY_ResetTerminal((*reinterpret_cast< TCP_COMM*(*)>(_a[1]))); break;
        case 111: _t->report_SZY_DeleteHistoryData((*reinterpret_cast< TCP_COMM*(*)>(_a[1]))); break;
        case 112: _t->report_SZY_OpenKDY((*reinterpret_cast< TCP_COMM*(*)>(_a[1]))); break;
        case 113: _t->report_SZY_CloseKDY((*reinterpret_cast< TCP_COMM*(*)>(_a[1]))); break;
        case 114: _t->report_SZY_SetThresholdStoreTime((*reinterpret_cast< TCP_COMM*(*)>(_a[1]))); break;
        case 115: _t->report_SZY_QueryRealTimeValue((*reinterpret_cast< TCP_COMM*(*)>(_a[1]))); break;
        case 116: _t->report_SZY_QueryData((*reinterpret_cast< TCP_COMM*(*)>(_a[1]))); break;
        case 117: _t->report_SZY_QueryUploadData((*reinterpret_cast< TCP_COMM*(*)>(_a[1]))); break;
        case 118: _t->report_SZY_QueryPicture((*reinterpret_cast< TCP_COMM*(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 119: _t->report_SZY_EnableIC((*reinterpret_cast< TCP_COMM*(*)>(_a[1]))); break;
        case 120: _t->report_SZY_DisableIC((*reinterpret_cast< TCP_COMM*(*)>(_a[1]))); break;
        case 121: _t->report_SZY_fixed_time((*reinterpret_cast< uint8_t(*)>(_a[1]))); break;
        case 122: { QString _r = _t->camera_fun((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])),(*reinterpret_cast< QString(*)>(_a[3])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 123: { bool _r = _t->report_pwCheck((*reinterpret_cast< QByteArray(*)>(_a[1])),(*reinterpret_cast< uint32_t(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 124: _t->timerTimeout_receive(); break;
        case 125: { uint16_t _r = _t->ModBusCRC16((*reinterpret_cast< QByteArray(*)>(_a[1])),(*reinterpret_cast< uint32_t(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< uint16_t*>(_a[0]) = std::move(_r); }  break;
        case 126: { uint8_t _r = _t->CRC8_SZY((*reinterpret_cast< QByteArray(*)>(_a[1])),(*reinterpret_cast< uint16_t(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< uint8_t*>(_a[0]) = std::move(_r); }  break;
        case 127: _t->serial_send_disconnect(); break;
        case 128: { uint32_t _r = _t->uwordToBcd((*reinterpret_cast< uint32_t(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< uint32_t*>(_a[0]) = std::move(_r); }  break;
        case 129: { uint32_t _r = _t->wordToBcd((*reinterpret_cast< int32_t(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< uint32_t*>(_a[0]) = std::move(_r); }  break;
        case 130: { uint32_t _r = _t->wordTo3Bcd((*reinterpret_cast< int32_t(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< uint32_t*>(_a[0]) = std::move(_r); }  break;
        case 131: { uint32_t _r = _t->uwordTo3Bcd((*reinterpret_cast< uint32_t(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< uint32_t*>(_a[0]) = std::move(_r); }  break;
        case 132: { uint64_t _r = _t->udwordToDBcd((*reinterpret_cast< uint64_t(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< uint64_t*>(_a[0]) = std::move(_r); }  break;
        case 133: { uint8_t _r = _t->byteToBcd((*reinterpret_cast< uint8_t(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< uint8_t*>(_a[0]) = std::move(_r); }  break;
        case 134: { uint8_t _r = _t->BCDtobyte((*reinterpret_cast< uint8_t(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< uint8_t*>(_a[0]) = std::move(_r); }  break;
        case 135: { uint16_t _r = _t->BCDtoHalfword((*reinterpret_cast< uint16_t(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< uint16_t*>(_a[0]) = std::move(_r); }  break;
        case 136: { int32_t _r = _t->bcdToWord((*reinterpret_cast< QByteArray(*)>(_a[1])),(*reinterpret_cast< uint32_t(*)>(_a[2])),(*reinterpret_cast< uint8_t(*)>(_a[3])),(*reinterpret_cast< bool(*)>(_a[4])));
            if (_a[0]) *reinterpret_cast< int32_t*>(_a[0]) = std::move(_r); }  break;
        case 137: { uint32_t _r = _t->bcdToUword((*reinterpret_cast< QByteArray(*)>(_a[1])),(*reinterpret_cast< uint32_t(*)>(_a[2])),(*reinterpret_cast< uint8_t(*)>(_a[3])));
            if (_a[0]) *reinterpret_cast< uint32_t*>(_a[0]) = std::move(_r); }  break;
        case 138: _t->Delay_MSec((*reinterpret_cast< uint(*)>(_a[1]))); break;
        case 139: { char _r = _t->convertHexChart((*reinterpret_cast< char(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< char*>(_a[0]) = std::move(_r); }  break;
        case 140: _t->StringToHex((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QByteArray(*)>(_a[2]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (tcp_socket::*)(uint8_t );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&tcp_socket::uploadTime)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (tcp_socket::*)(QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&tcp_socket::uploadPassword)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (tcp_socket::*)(int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&tcp_socket::kdy_signal)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (tcp_socket::*)(int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&tcp_socket::uploadBaseSet)) {
                *result = 3;
                return;
            }
        }
        {
            using _t = void (tcp_socket::*)(int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&tcp_socket::uploadRunSet)) {
                *result = 4;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject tcp_socket::staticMetaObject = { {
    &QWidget::staticMetaObject,
    qt_meta_stringdata_tcp_socket.data,
    qt_meta_data_tcp_socket,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *tcp_socket::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *tcp_socket::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_tcp_socket.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int tcp_socket::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 141)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 141;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 141)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 141;
    }
    return _id;
}

// SIGNAL 0
void tcp_socket::uploadTime(uint8_t _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void tcp_socket::uploadPassword(QString _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void tcp_socket::kdy_signal(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void tcp_socket::uploadBaseSet(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void tcp_socket::uploadRunSet(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
