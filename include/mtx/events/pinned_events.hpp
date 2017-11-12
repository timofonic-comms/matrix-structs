#pragma once

#include <json.hpp>
#include <string>

using json = nlohmann::json;

namespace mtx {
namespace events {
namespace state {

struct PinnedEvents
{
        std::vector<std::string> pinned;
};

void
from_json(const json &obj, PinnedEvents &event)
{
        event.pinned = obj.at("pinned").get<std::vector<std::string>>();
}

void
to_json(json &obj, const PinnedEvents &event)
{
        obj["pinned"] = event.pinned;
}

} // namespace state
} // namespace events
} // namespace mtx
