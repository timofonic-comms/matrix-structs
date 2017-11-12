#pragma once

#include <json.hpp>
#include <string>

using json = nlohmann::json;

namespace mtx {
namespace events {
namespace state {

struct Name
{
        std::string name;
};

void
from_json(const json &obj, Name &event)
{
        event.name = obj.at("name").get<std::string>();
}

void
to_json(json &obj, const Name &event)
{
        obj["name"] = event.name;
}

} // namespace state
} // namespace events
} // namespace mtx
