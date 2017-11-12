#pragma once

#include <json.hpp>
#include <string>

using json = nlohmann::json;

namespace mtx {
namespace events {
namespace state {

struct Create
{
        mtx::identifiers::User creator;
        bool federate;
};

void
from_json(const json &obj, Create &create)
{
        using namespace mtx::identifiers;
        create.creator = parse<User>(obj.at("creator").get<std::string>());

        if (obj.find("m.federate") != obj.end())
                create.federate = obj.at("m.federate").get<bool>();
}

void
to_json(json &obj, const Create &create)
{
        obj["creator"]    = create.creator.toString();
        obj["m.federate"] = create.federate;
}

} // namespace state
} // namespace events
} // namespace mtx
