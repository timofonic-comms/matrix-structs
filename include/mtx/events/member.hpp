#pragma once

#include <json.hpp>
#include <string>

using json = nlohmann::json;

namespace mtx {
namespace events {
namespace state {

enum class Membership
{
        // The user has joined.
        Join,
        // The user has been invited.
        Invite,
        // The user is banned.
        Ban,
        // The user has left.
        Leave,
        // The user has requested to join.
        Knock,
};

std::string
membershipToString(const Membership &membership)
{
        switch (membership) {
        case Membership::Join:
                return "join";
        case Membership::Invite:
                return "invite";
        case Membership::Ban:
                return "ban";
        case Membership::Leave:
                return "leave";
        case Membership::Knock:
                return "knock";
        }
}

Membership
stringToMembership(const std::string &membership)
{
        if (membership == "join")
                return Membership::Join;
        else if (membership == "invite")
                return Membership::Invite;
        else if (membership == "ban")
                return Membership::Ban;
        else if (membership == "leave")
                return Membership::Leave;

        return Membership::Knock;
}

struct Member
{
        Membership membership;
        std::string avatar_url;
        std::string display_name;

        /* ThirdPartyInvite third_party_invite; */
        bool is_direct = false;
};

void
from_json(const json &obj, Member &member)
{
        member.membership   = stringToMembership(obj.at("membership").get<std::string>());
        member.avatar_url   = obj.at("avatar_url").get<std::string>();
        member.display_name = obj.at("displayname").get<std::string>();

        if (obj.find("is_direct") != obj.end())
                member.is_direct = obj.at("is_direct").get<bool>();
}

void
to_json(json &obj, const Member &member)
{
        obj["membership"]  = membershipToString(member.membership);
        obj["avatar_url"]  = member.avatar_url;
        obj["displayname"] = member.display_name;
        obj["is_direct"]   = member.is_direct;
}

} // namespace state
} // namespace events
} // namespace mtx
