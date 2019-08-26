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
        double lattitude;
        double longitude;
        float altitude;
        std::time_t time;
    };

    struct CameraPropertyPayload
    {
        unsigned int id;
        float value;
    };

    struct CameraCommand
    {
        enum CommandType : std::uint8_t
        {
            DoPhoto = 0,
            StartRecord,
            StopRecord,
            SetProperty,
            CountProperties,
            GetProperty
        };
        CommandType type;

        union
        {
            CameraPropertyPayload property;
            CameraDoPhotoPayload doPhoto;
        } payload;
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
        
        float value;
    } __attribute__((packed));
};

#endif
