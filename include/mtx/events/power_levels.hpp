#pragma once

#include <json.hpp>
#include <string>

using json = nlohmann::json;

namespace mtx {
namespace events {
namespace state {

constexpr uint16_t EventsDefault = 0;
constexpr uint16_t UsersDefault  = 0;
constexpr uint16_t StatesDefault = 50;

constexpr uint16_t User      = 0;
constexpr uint16_t Moderator = 50;
constexpr uint16_t Admin     = 100;

struct PowerLevels
{
        int eventLevel(std::string event_type) const;
        int userLevel(std::string user_id) const;

        uint16_t ban    = Moderator;
        uint16_t invite = Moderator;
        uint16_t kick   = Moderator;
        uint16_t redact = Moderator;

        uint16_t events_default = User;
        uint16_t users_default  = User;
        uint16_t state_default  = Moderator;

        std::map<std::string, uint16_t> events;
        std::map<std::string, uint16_t> users;
};

void
from_json(const json &obj, PowerLevels &power_levels)
{
        power_levels.ban    = obj.at("ban").get<uint16_t>();
        power_levels.invite = obj.at("invite").get<uint16_t>();
        power_levels.kick   = obj.at("kick").get<uint16_t>();
        power_levels.redact = obj.at("redact").get<uint16_t>();

        power_levels.events = obj.at("events").get<std::map<std::string, uint16_t>>();
        power_levels.users  = obj.at("users").get<std::map<std::string, uint16_t>>();

        power_levels.events_default = obj.at("events_default").get<uint16_t>();
        power_levels.users_default  = obj.at("users_default").get<uint16_t>();
        power_levels.state_default  = obj.at("state_default").get<uint16_t>();
}

void
to_json(json &obj, const PowerLevels &power_levels)
{
        obj["ban"]    = power_levels.ban;
        obj["kick"]   = power_levels.kick;
        obj["invite"] = power_levels.invite;
        obj["redact"] = power_levels.redact;

        obj["events"] = power_levels.events;
        obj["users"]  = power_levels.users;

        obj["events_default"] = power_levels.events_default;
        obj["users_default"]  = power_levels.users_default;
        obj["state_default"]  = power_levels.state_default;
}

} // namespace state
} // namespace events
} // namespace mtx
