local ffi = require("ffi")

ffi.cdef[[
typedef struct AVFormatContext AVFormatContext;
typedef struct AVCodecContext AVCodecContext;
typedef struct AVPacket AVPacket;
typedef struct AVFrame AVFrame;

int avformat_open_input(AVFormatContext **ps, const char *url, void *fmt, void *options);
int avformat_find_stream_info(AVFormatContext *ic, void *options);
int avcodec_find_decoder(enum AVCodecID id);
int avcodec_open2(AVCodecContext *avctx, const void *codec, void *options);
int av_read_frame(AVFormatContext *s, AVPacket *pkt);
int avcodec_send_packet(AVCodecContext *avctx, const AVPacket *avpkt);
int avcodec_receive_frame(AVCodecContext *avctx, AVFrame *frame);
void av_packet_unref(AVPacket *pkt);
void av_frame_unref(AVFrame *frame);
void avcodec_close(AVCodecContext *avctx);
void avformat_close_input(AVFormatContext **s);
void avformat_free_context(AVFormatContext *s);
void av_frame_free(AVFrame **frame);
void av_free(void *ptr);
]]

local av = ffi.load("avcodec")

local url = "your_video_file.mp4" -- Replace this with your video file path

local avFormatCtx = ffi.new("AVFormatContext*[1]")
local avCodecCtx = ffi.new("AVCodecContext*[1]")
local avFrame = ffi.new("AVFrame*[1]")
local avPacket = ffi.new("AVPacket")

-- Open video file
if av.avformat_open_input(avFormatCtx, url, nil, nil) ~= 0 then
    print("Error: Could not open file")
    return
end

-- Retrieve stream information
if av.avformat_find_stream_info(avFormatCtx[0], nil) < 0 then
    print("Error: Could not find stream information")
    return
end

-- Find the first video stream
local videoStreamIndex = -1
for i = 0, avFormatCtx[0].nb_streams - 1 do
    if avFormatCtx[0].streams[i].codecpar.codec_type == 0 then
        videoStreamIndex = i
        break
    end
end

if videoStreamIndex == -1 then
    print("Error: Could not find video stream")
    return
end

-- Get a pointer to the codec context for the video stream
avCodecCtx[0] = avFormatCtx[0].streams[videoStreamIndex].codec

-- Find the decoder for the video stream
local avCodec = av.avcodec_find_decoder(avCodecCtx[0].codec_id)
if avCodec == nil then
    print("Error: Unsupported codec")
    return
end

-- Open codec
if av.avcodec_open2(avCodecCtx[0], avCodec, nil) < 0 then
    print("Error: Could not open codec")
    return
end

-- Read frames
while av.av_read_frame(avFormatCtx[0], avPacket) >= 0 do
    if avPacket.stream_index == videoStreamIndex then
        if av.avcodec_send_packet(avCodecCtx[0], avPacket) == 0 then
            while av.avcodec_receive_frame(avCodecCtx[0], avFrame[0]) == 0 do
                -- Do something with the frame, for example, print its width and height
                print("Frame Width: ", avCodecCtx[0].width)
                print("Frame Height: ", avCodecCtx[0].height)

                -- Unreference the frame
                av.av_frame_unref(avFrame[0])
            end
        end
    end

    -- Unreference the packet
    av.av_packet_unref(avPacket)
end

-- Clean up
av.avcodec_close(avCodecCtx[0])
av.avformat_close_input(avFormatCtx)
av.avformat_free_context(avFormatCtx[0])
av.av_frame_free(avFrame)

