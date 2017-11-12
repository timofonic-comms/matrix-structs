#pragma once

#include <json.hpp>
#include <string>

#include "../common.hpp"

using json = nlohmann::json;

namespace common = mtx::common;

namespace mtx {
namespace events {
namespace msg {

struct Image
{
        // A textual representation of the image. This could be
        // the alt text of the image, the filename of the image,
        // or some kind of content description for accessibility e.g. 'image attachment
        std::string body;
        // Must be 'm.image'.
        std::string msgtype;
        // The Matrix URL to the image.
        std::string url;
        // Metadata about the image referred to in `url`.
        common::ImageInfo info;
};

void
from_json(const json &obj, Image &content)
{
        content.body    = obj.at("body").get<std::string>();
        content.msgtype = obj.at("msgtype").get<std::string>();
        content.url     = obj.at("url").get<std::string>();

        if (obj.find("info") != obj.end())
                content.info = obj.at("info").get<common::ImageInfo>();
}

void
to_json(json &obj, const Image &content)
{
        obj["msgtype"] = "m.image";
        obj["body"]    = content.body;
        obj["url"]     = content.url;
        obj["info"]    = content.info;
}

} // namespace msg
} // namespace events
} // namespace mtx
