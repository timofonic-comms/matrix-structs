#pragma once

#include <json.hpp>
#include <string>

using json = nlohmann::json;

namespace mtx {
namespace events {
namespace state {

struct Topic
{
        std::string topic;
};

void
from_json(const json &obj, Topic &event)
{
        event.topic = obj.at("topic").get<std::string>();
}

void
to_json(json &obj, const Topic &event)
{
        obj["topic"] = event.topic;
}

} // namespace state
} // namespace events
} // namespace mtx
