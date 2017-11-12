#pragma once

#include <json.hpp>

using json = nlohmann::json;

namespace mtx {
namespace events {
namespace state {

struct Aliases
{
        std::vector<std::string> aliases;
};

void
from_json(const json &obj, Aliases &content)
{
        content.aliases = obj.at("aliases").get<std::vector<std::string>>();
}

void
to_json(json &obj, const Aliases &content)
{
        obj["aliases"] = content.aliases;
}

} // namespace state
} // namespace events
} // namespace mtx
