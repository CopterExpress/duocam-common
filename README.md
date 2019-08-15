# DuoCam Camera Driver and MAVLink Service Intercommunication Protocol

The protocol is based on **POSIX message queues** (https://linux.die.net/man/7/mq_overview). Every side is responsible for the creation and the destruction of the **recieving** queue (that means the application has to **unlink** the queue before the exit). Camera driver creates a queue of **DuocamCommon::CameraCommand** messages, MAVLink service - a queue of **DuocamCommon::CameraAnswer** messages. Every queue must have a **mq_maxmsg** attribute equal to **sizeof()** of the message. The queues paths are fixed and located in the **DuocamCommon::QueuePaths** namespace.

## DuocamCommon::CameraCommand

On the external event MAVLink service creates **DuocamCommon::CameraCommand** message and sends it to the queue. The possible command types:
- **DuocamCommon::CommandType::DoPhoto** - take a photo immiditely and write data from doPhotoPayload to EXIF.
- **DuocamCommon::CommandType::StartRecord** - start a video record.
- **DuocamCommon::CommandType::StopRecond** - stop a video record.

MAVLink service waits configurable command timeout time for an answer from CameraDriver. If the answer isn't arrived, the command is marked as failed.

**WARNING!** If **NO GPS** mode is enabled, the camera coordinates and altitude are set to **NaN**.

## DuocamCommon::CameraAnswer

The camera driver sends an answer **only** when the operation is completed/failed and the driver is ready to recieve a new command of the **same type** (**DuocamCommon::CameraAnswer::type**). Possible answer types:
- **Ack** - the operation has been successfully completed. 
- **Nack** - the operation has failed.

In case the operation fails the camera driver can specify a string description of the error happened in **DuocamCommon::CameraAnswer::result** field. The maximum length of the comment can be determined from **DuocamCommon::cameraAnswerCommentSize**.
