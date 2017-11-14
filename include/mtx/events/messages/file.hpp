#pragma once

#include <json.hpp>
#include <string>

#include "../common.hpp"

using json = nlohmann::json;

namespace common = mtx::common;

namespace mtx {
namespace events {
namespace msg {

struct File
{
        // A human-readable description of the file. This is recommended to
        // be the filename of the original upload.
        std::string body;
        // The original filename of the uploaded file.
        // SPEC_BUG: The filename is not really required.
        std::string filename;
        // Must be 'm.file'.
        std::string msgtype;
        // The matrix URL of the file.
        std::string url;
        // Information about the file referred to in the url.
        common::FileInfo info;
};

void
from_json(const json &obj, File &content)
{
        content.body    = obj.at("body").get<std::string>();
        content.msgtype = obj.at("msgtype").get<std::string>();

        if (obj.find("url") != obj.end())
                content.url = obj.at("url").get<std::string>();

        if (obj.find("filename") != obj.end())
                content.filename = obj.at("filename").get<std::string>();

        if (obj.find("info") != obj.end())
                content.info = obj.at("info").get<common::FileInfo>();
}

void
to_json(json &obj, const File &content)
{
        obj["msgtype"]  = "m.file";
        obj["body"]     = content.body;
        obj["filename"] = content.filename;
        obj["url"]      = content.url;
        obj["info"]     = content.info;
}

} // namespace msg
} // namespace events
} // namespace mtx
