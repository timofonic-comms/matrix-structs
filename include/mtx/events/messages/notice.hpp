#pragma once

#include <json.hpp>
#include <string>

using json = nlohmann::json;

namespace mtx {
namespace events {
namespace msg {

struct Notice
{
        // The notice text to send.
        std::string body;
        // Must be 'm.notice'.
        std::string msgtype;
};

void
from_json(const json &obj, Notice &content)
{
        content.body    = obj.at("body").get<std::string>();
        content.msgtype = obj.at("msgtype").get<std::string>();
}

void
to_json(json &obj, const Notice &content)
{
        obj["msgtype"] = "m.notice";
        obj["body"]    = content.body;
}

} // namespace msg
} // namespace events
} // namespace mtx
