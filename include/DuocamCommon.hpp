#ifndef DUOCAM_COMMON_MQ_INTERFACE
#define DUOCAM_COMMON_MQ_INTERFACE

#include <string>
#include <ctime>
#include <cstdint>

namespace DuocamCommon
{
    namespace QueuePaths
    {
        const char* const Camera = "/duocam_camera";
        const char* const Mavlink = "/duocam_mavlink";
    };

    struct CameraDoPhotoPayload
    {
        float duration;
        double lattitude;
        double longitude;
        float altitude;
        std::time_t time;
    };

    struct CameraCommand
    {
        enum CommandType : std::uint8_t
        {
            DoPhoto = 0,
            StartRecord,
            StopRecord
        };

        CommandType type;

        CameraDoPhotoPayload doPhotoPayload;
    } __attribute__((packed));

    const int cameraAnswerCommentSize = 40;

    struct CameraAnswer
    {
        CameraCommand::CommandType type;

        enum CommandResult : std::uint8_t
        {
            Ack = 0,
            Nack
        };
        
        CommandResult result;

        char comment[cameraAnswerCommentSize + 1];
    } __attribute__((packed));
};

#endif