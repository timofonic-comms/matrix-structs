#pragma once

#include <json.hpp>

using json = nlohmann::json;

namespace mtx {
namespace common {

struct ThumbnailInfo
{
        uint64_t h;
        uint64_t w;
        uint64_t size;

        std::string mimetype;
};

void
from_json(const json &obj, ThumbnailInfo &info)
{
        info.h        = obj.at("h").get<uint64_t>();
        info.w        = obj.at("w").get<uint64_t>();
        info.size     = obj.at("size").get<uint64_t>();
        info.mimetype = obj.at("mimetype").get<std::string>();
}

void
to_json(json &obj, const ThumbnailInfo &info)
{
        obj["h"]        = info.h;
        obj["w"]        = info.w;
        obj["size"]     = info.size;
        obj["mimetype"] = info.mimetype;
}

struct ImageInfo
{
        uint64_t h;
        uint64_t w;
        uint64_t size;

        ThumbnailInfo thumbnail_info;

        std::string thumbnail_url;
        std::string mimetype;
};

void
from_json(const json &obj, ImageInfo &info)
{
        info.h              = obj.at("h").get<uint64_t>();
        info.w              = obj.at("w").get<uint64_t>();
        info.size           = obj.at("size").get<uint64_t>();
        info.mimetype       = obj.at("mimetype").get<std::string>();
        info.thumbnail_url  = obj.at("thumbnail_url").get<std::string>();
        info.thumbnail_info = obj.at("thumbnail_info").get<ThumbnailInfo>();
}

void
to_json(json &obj, const ImageInfo &info)
{
        obj["h"]              = info.h;
        obj["w"]              = info.w;
        obj["size"]           = info.size;
        obj["mimetype"]       = info.mimetype;
        obj["thumbnail_url"]  = info.thumbnail_url;
        obj["thumbnail_info"] = info.thumbnail_info;
}

struct FileInfo
{
        // The size of the file in bytes.
        uint64_t size;
        // Metadata about the image referred to in `thumbnail_url`.
        ThumbnailInfo thumbnail_info;
        // The Matrix URL to the the thumbnail of the file.
        std::string thumbnail_url;
        // The mimetype of the file e.g `application/pdf`.
        std::string mimetype;
};

void
from_json(const json &obj, FileInfo &info)
{
        if (obj.find("size") != obj.end())
                info.size = obj.at("size").get<uint64_t>();

        if (obj.find("mimetype") != obj.end())
                info.mimetype = obj.at("mimetype").get<std::string>();

        if (obj.find("thumbnail_url") != obj.end())
                info.thumbnail_url = obj.at("thumbnail_url").get<std::string>();

        if (obj.find("thumbnail_info") != obj.end())
                info.thumbnail_info = obj.at("thumbnail_info").get<ThumbnailInfo>();
}

void
to_json(json &obj, const FileInfo &info)
{
        obj["size"]           = info.size;
        obj["mimetype"]       = info.mimetype;
        obj["thumbnail_url"]  = info.thumbnail_url;
        obj["thumbnail_info"] = info.thumbnail_info;
}

struct AudioInfo
{
        uint64_t size;
        uint64_t duration;
        std::string mimetype;
};

void
from_json(const json &obj, AudioInfo &info)
{
        info.duration = obj.at("duration").get<uint64_t>();
        info.size     = obj.at("size").get<uint64_t>();
        info.mimetype = obj.at("mimetype").get<std::string>();
}

void
to_json(json &obj, const AudioInfo &info)
{
        obj["size"]     = info.size;
        obj["duration"] = info.duration;
        obj["mimetype"] = info.mimetype;
}

struct VideoInfo
{
        // The size of the video in bytes.
        uint64_t size;
        // The duration of the video in milliseconds.
        uint64_t duration;
        // The height of the video in pixels.
        uint64_t h;
        // The width of the video in pixels.
        uint64_t w;
        // The mimetype of the video e.g. video/mp4.
        std::string mimetype;
        // The URL to an image thumbnail of the video clip.
        std::string thumbnail_url;
        // Metadata about the image referred to in thumbnail_url.
        ThumbnailInfo thumbnail_info;
};

void
from_json(const json &obj, VideoInfo &info)
{
        if (obj.find("w") != obj.end())
                info.w = obj.at("w").get<uint64_t>();

        if (obj.find("h") != obj.end())
                info.h = obj.at("h").get<uint64_t>();

        if (obj.find("size") != obj.end())
                info.size = obj.at("size").get<uint64_t>();

        if (obj.find("duration") != obj.end())
                info.duration = obj.at("duration").get<uint64_t>();

        if (obj.find("mimetype") != obj.end())
                info.mimetype = obj.at("mimetype").get<std::string>();

        if (obj.find("thumbnail_url") != obj.end())
                info.thumbnail_url = obj.at("thumbnail_url").get<std::string>();

        if (obj.find("thumbnail_info") != obj.end())
                info.thumbnail_info = obj.at("thumbnail_info").get<ThumbnailInfo>();
}

void
to_json(json &obj, const VideoInfo &info)
{
        obj["size"]           = info.size;
        obj["h"]              = info.h;
        obj["w"]              = info.w;
        obj["duration"]       = info.duration;
        obj["thumbnail_url"]  = info.thumbnail_url;
        obj["thumbnail_info"] = info.thumbnail_info;
        obj["mimetype"]       = info.mimetype;
}

} // namespace common
} // namespace mtx
