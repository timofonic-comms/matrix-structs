#pragma once

#include <json.hpp>

using json = nlohmann::json;

namespace mtx {
namespace events {

enum class EventType
{
        /// m.room.aliases
        RoomAliases,
        /// m.room.avatar
        RoomAvatar,
        /// m.room.canonical_alias
        RoomCanonicalAlias,
        /// m.room.create
        RoomCreate,
        /// m.room.history_visibility
        RoomHistoryVisibility,
        /// m.room.join_rules
        RoomJoinRules,
        /// m.room.member
        RoomMember,
        /// m.room.message
        RoomMessage,
        /// m.room.name
        RoomName,
        /// m.room.power_levels
        RoomPowerLevels,
        /// m.room.topic
        RoomTopic,
        /// m.room.redaction
        RoomRedaction,
        /// m.room.pinned_events
        RoomPinnedEvents,
        // Unsupported event
        Unsupported,
};

EventType
getEventType(const std::string &type)
{
        if (type == "m.room.aliases")
                return EventType::RoomAliases;
        else if (type == "m.room.avatar")
                return EventType::RoomAvatar;
        else if (type == "m.room.canonical_alias")
                return EventType::RoomCanonicalAlias;
        else if (type == "m.room.create")
                return EventType::RoomCreate;
        else if (type == "m.room.history_visibility")
                return EventType::RoomHistoryVisibility;
        else if (type == "m.room.join_rules")
                return EventType::RoomJoinRules;
        else if (type == "m.room.member")
                return EventType::RoomMember;
        else if (type == "m.room.message")
                return EventType::RoomMessage;
        else if (type == "m.room.name")
                return EventType::RoomName;
        else if (type == "m.room.power_levels")
                return EventType::RoomPowerLevels;
        else if (type == "m.room.topic")
                return EventType::RoomTopic;
        else if (type == "m.room.redaction")
                return EventType::RoomRedaction;
        else if (type == "m.room.pinned_events")
                return EventType::RoomPinnedEvents;

        return EventType::Unsupported;
}

EventType
getEventType(const json &obj)
{
        if (obj.find("type") != obj.end())
                return getEventType(obj.at("type").get<std::string>());

        return EventType::Unsupported;
}

template<class Content>
struct Event
{
        Content content;
        EventType type;
};

template<class Content>
void
to_json(json &obj, const Event<Content> &event)
{
        obj["content"] = json{event.content};

        switch (event.type) {
        case EventType::RoomAliases:
                obj["type"] = "m.room.aliases";
                break;
        case EventType::RoomAvatar:
                obj["type"] = "m.room.avatar";
                break;
        case EventType::RoomCanonicalAlias:
                obj["type"] = "m.room.canonical_alias";
                break;
        case EventType::RoomCreate:
                obj["type"] = "m.room.create";
                break;
        case EventType::RoomHistoryVisibility:
                obj["type"] = "m.room.history_visibility";
                break;
        case EventType::RoomJoinRules:
                obj["type"] = "m.room.join_rules";
                break;
        case EventType::RoomMember:
                obj["type"] = "m.room.member";
                break;
        case EventType::RoomMessage:
                obj["type"] = "m.room.message";
                break;
        case EventType::RoomName:
                obj["type"] = "m.room.name";
                break;
        case EventType::RoomPowerLevels:
                obj["type"] = "m.room.power_levels";
                break;
        case EventType::RoomTopic:
                obj["type"] = "m.room.topic";
                break;
        case EventType::RoomRedaction:
                obj["type"] = "m.room.redaction";
                break;
        case EventType::RoomPinnedEvents:
                obj["type"] = "m.room.pinned_events";
                break;
        case EventType::Unsupported:
                std::cout << "Unsupported type to serialize" << std::endl;
                break;
        }
}

template<class Content>
void
from_json(const json &obj, Event<Content> &event)
{
        event.content = obj.at("content").get<Content>();
        event.type    = getEventType(obj.at("type").get<std::string>());
}

template<class Content>
struct UnsignedData
{
        uint64_t age;
        std::string transaction_id;
        std::string prev_sender;
        std::string replaces_state;

        Content prev_content;
};

template<class Content>
void
from_json(const json &obj, UnsignedData<Content> &data)
{
        if (obj.find("age") != obj.end())
                data.age = obj.at("age").get<uint64_t>();

        if (obj.find("transaction_id") != obj.end())
                data.transaction_id = obj.at("transaction_id").get<std::string>();

        if (obj.find("prev_sender") != obj.end())
                data.prev_sender = obj.at("prev_sender").get<std::string>();

        if (obj.find("replaces_state") != obj.end())
                data.replaces_state = obj.at("replaces_state").get<std::string>();

        if (obj.find("prev_content") != obj.end())
                data.prev_content = obj.at("prev_content").get<Content>();
}

template<class Content>
void
to_json(json &obj, const UnsignedData<Content> &event)
{
        obj["age"]            = event.age;
        obj["transaction_id"] = event.transaction_id;
        obj["prev_sender"]    = event.prev_sender;
        obj["replaces_state"] = event.replaces_state;
        obj["prev_content"]   = event.prev_content;
}

template<class Content>
struct RoomEvent : public Event<Content>
{
        std::string event_id;
        std::string room_id;
        std::string sender;

        uint64_t origin_server_ts;

        // SPEC_BUG: The contents of unsigned_data are also present as top level keys.
        UnsignedData<Content> unsigned_data;
};

template<class Content>
void
from_json(const json &obj, RoomEvent<Content> &event)
{
        Event<Content> base_event = event;
        from_json(obj, base_event);

        event.content          = base_event.content;
        event.type             = base_event.type;
        event.event_id         = obj.at("event_id").get<std::string>();
        event.sender           = obj.at("sender").get<std::string>();
        event.origin_server_ts = obj.at("origin_server_ts").get<double>();

        // SPEC_BUG: Not present in the state array returned by /sync.
        if (obj.find("room_id") != obj.end())
                event.room_id = obj.at("room_id").get<std::string>();

        if (obj.find("unsigned") != obj.end())
                event.unsigned_data = obj.at("unsigned").get<UnsignedData<Content>>();
}

template<class Content>
void
to_json(json &obj, const RoomEvent<Content> &event)
{
        obj["event_id"]         = event.event_id;
        obj["room_id"]          = event.room_id;
        obj["sender"]           = event.sender;
        obj["unsigned"]         = event.unsigned_data;
        obj["origin_server_ts"] = event.origin_server_ts;
}

template<class Content>
struct StateEvent : public RoomEvent<Content>
{
        std::string state_key;
        Content prev_content;
};

template<class Content>
void
to_json(json &obj, const StateEvent<Content> &event)
{
        obj["state_key"]    = event.state_key;
        obj["prev_content"] = json{event.prev_content};
}

template<class Content>
void
from_json(const json &obj, StateEvent<Content> &event)
{
        RoomEvent<Content> base_event = event;
        from_json(obj, base_event);

        event.content          = base_event.content;
        event.type             = base_event.type;
        event.event_id         = base_event.event_id;
        event.room_id          = base_event.room_id;
        event.sender           = base_event.sender;
        event.origin_server_ts = base_event.origin_server_ts;
        event.unsigned_data    = base_event.unsigned_data;

        event.state_key = obj.at("state_key").get<std::string>();

        if (obj.find("prev_content") != obj.end())
                event.prev_content = obj.at("prev_content").get<Content>();
}

enum class MessageType
{
        // m.audio
        Audio,
        // m.emote
        Emote,
        // m.file
        File,
        // m.image
        Image,
        // m.location
        Location,
        // m.notice
        Notice,
        // m.text
        Text,
        // m.video
        Video,
        // Unrecognized message type
        Unknown,
};

MessageType
getMessageType(const std::string &type)
{
        if (type == "m.audio")
                return MessageType::Audio;
        else if (type == "m.emote")
                return MessageType::Emote;
        else if (type == "m.file")
                return MessageType::File;
        else if (type == "m.image")
                return MessageType::Image;
        else if (type == "m.location")
                return MessageType::Location;
        else if (type == "m.notice")
                return MessageType::Notice;
        else if (type == "m.text")
                return MessageType::Text;
        else if (type == "m.video")
                return MessageType::Video;

        return MessageType::Unknown;
}

MessageType
getMessageType(const json &obj)
{
        if (obj.is_null())
                return MessageType::Unknown;

        if (obj.find("msgtype") == obj.end())
                return MessageType::Unknown;

        return getMessageType(obj.at("msgtype").get<std::string>());
}

} // namespace events
} // namespace mtx
