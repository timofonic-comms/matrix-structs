#pragma once

#include <json.hpp>
#include <string>

using json = nlohmann::json;

namespace mtx {
namespace events {
namespace state {

enum class AccessState
{
        CanJoin,
        Forbidden,
};

std::string
accessStateToString(AccessState state)
{
        if (state == AccessState::CanJoin)
                return "can_join";

        return "forbidden";
}

AccessState
stringToAccessState(const std::string &state)
{
        if (state == "can_join")
                return AccessState::CanJoin;

        return AccessState::Forbidden;
}

struct GuestAccess
{
        AccessState guest_access = AccessState::Forbidden;
};

void
from_json(const json &obj, GuestAccess &guest_access)
{
        guest_access.guest_access = stringToAccessState(obj.at("guest_access").get<std::string>());
}

void
to_json(json &obj, const GuestAccess &guest_access)
{
        obj["guest_access"] = accessStateToString(guest_access.guest_access);
}

} // namespace state
} // namespace events
} // namespace mtx
