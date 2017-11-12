#pragma once

#include <json.hpp>
#include <string>

using json = nlohmann::json;

namespace mtx {
namespace events {
namespace msg {

struct Text
{
        // The body of the message.
        std::string body;
        // Must be 'm.text'.
        std::string msgtype;
};

void
from_json(const json &obj, Text &content)
{
        content.body    = obj.at("body").get<std::string>();
        content.msgtype = obj.at("msgtype").get<std::string>();
}

void
to_json(json &obj, const Text &content)
{
        obj["msgtype"] = "m.text";
        obj["body"]    = content.body;
}

} // namespace msg
} // namespace events
} // namespace mtx
