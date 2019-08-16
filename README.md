# DuoCam Camera Driver and MAVLink Service Intercommunication Protocol

The protocol is based on **POSIX message queues** (https://linux.die.net/man/7/mq_overview). Camera driver is responsible for the creation and the destruction of the **DuocamCommon::CameraCommand** and **DuocamCommon::CameraAnswer** message queues (that means the application has to **unlink** the queues before the exit). Every queue must have a **mq_maxmsg** attribute equal to **sizeof()** of the message. The queues paths are fixed and located in the **DuocamCommon::QueuePaths** namespace.

## DuocamCommon::CameraCommand

On the external event MAVLink service creates **DuocamCommon::CameraCommand** message and sends it to the queue. The possible command types:
- **DuocamCommon::CommandType::DoPhoto** - take a photo immiditely and write data from doPhotoPayload to EXIF.
- **DuocamCommon::CommandType::StartRecord** - start a video record.
- **DuocamCommon::CommandType::StopRecond** - stop a video record.
- **DuocamCommon::CommandType::ChangeProperty** - change a camera property.
- **DuocamCommon::CommandType::CountProperties** - get camera properties count.
- **DuocamCommon::CommandType::GetProperty** - get a camera property value.

Command has a payload that depends on the command type.

MAVLink service waits configurable command timeout time for an answer from CameraDriver. If the answer isn't arrived, the command is marked as failed.

**WARNING!** If **NO GPS** mode is enabled, the camera coordinates and altitude are set to **NaN**.

## DuocamCommon::CameraAnswer

The camera driver sends an answer **only** when the operation is completed/failed and the driver is ready to recieve a new command of the **same type** (**DuocamCommon::CameraAnswer::result**). Possible answer types:
- **Ack** - the operation has been successfully completed. 
- **Nack** - the operation has failed.

In case the operation fails the camera driver can specify a string description of the error happened in **DuocamCommon::CameraAnswer::comment** field. The maximum length of the comment can be determined from **DuocamCommon::cameraAnswerCommentSize**.

Optional field **DuocamCommon::CameraAnswer::value** can be used to add a numeric payload to the answer.
