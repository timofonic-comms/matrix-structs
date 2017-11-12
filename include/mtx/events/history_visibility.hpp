#pragma once

#include <json.hpp>
#include <string>

using json = nlohmann::json;

namespace mtx {
namespace events {
namespace state {

enum class Visibility
{
        // All events while this is the m.room.history_visibility
        // value may be shared by any participating homeserver with anyone,
        // regardless of whether they have ever joined the room.
        WorldReadable,
        // Previous events are always accessible to newly joined members.
        // All events in the room are accessible, even those sent when
        // the member was not a part of the room.
        Shared,
        // Events are accessible to newly joined members from the point
        // they were invited onwards. Events stop being accessible when
        // the member's state changes to something other than invite or join.
        Invited,
        // Events are accessible to newly joined members from the point
        // they joined the room onwards. Events stop being accessible
        // when the member's state changes to something other than join.
        Joined,
};

std::string
visibilityToString(const Visibility &rule)
{
        switch (rule) {
        case Visibility::WorldReadable:
                return "world_readable";
        case Visibility::Invited:
                return "invited";
        case Visibility::Shared:
                return "shared";
        case Visibility::Joined:
                return "joined";
        }

        return "";
}

Visibility
stringToVisibility(const std::string &rule)
{
        if (rule == "world_readable")
                return Visibility::WorldReadable;
        else if (rule == "invited")
                return Visibility::Invited;
        else if (rule == "shared")
                return Visibility::Shared;

        return Visibility::Joined;
}

struct HistoryVisibility
{
        Visibility history_visibility;
};

void
from_json(const json &obj, HistoryVisibility &event)
{
        event.history_visibility =
          stringToVisibility(obj.at("history_visibility").get<std::string>());
}

void
to_json(json &obj, const HistoryVisibility &event)
{
        obj["history_visibility"] = visibilityToString(event.history_visibility);
}

} // namespace state
} // namespace events
} // namespace mtx
