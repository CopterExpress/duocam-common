#ifndef DUOCAM_COMMON_MQ_INTERFACE
#define DUOCAM_COMMON_MQ_INTERFACE

#include <string>
#include <ctime>
#include <cstdint>

namespace DuocamCommon
{
    namespace QueuePaths
    {
            inline static const std::string Camera = "/duocam_camera";
            inline static const std::string Mavlink = "/duocam_mavlink";
    };

    struct CameraDoPhotoPayload
    {
        double lattitude;
        double longitude;
        float altitude;
        std::time_t time;
    };

    struct CameraCommand
    {
        enum MessageType : std::uint8_t
        {
            DoPhoto = 0,
            StartRecord,
            StopRecond
        };

        MessageType type;

        CameraDoPhotoPayload doPhotoPayload;
    } __attribute__((packed));

    inline static const int cameraAnswerCommentSize = 40;

    struct CameraAnswer
    {
        enum MessageType : std::uint8_t
        {
            Ack = 0,
            Nack
        };

        MessageType type;

        char comment[cameraAnswerCommentSize + 1];
    } __attribute__((packed));
};

#endif