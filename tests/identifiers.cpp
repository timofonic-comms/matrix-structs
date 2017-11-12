#include <gtest/gtest.h>

#include <mtx.hpp>

using namespace mtx::identifiers;

TEST(MatrixIdentifiers, EventValid)
{
        Event eventid = parse<Event>("$39hvsi03hlne:example.com");

        EXPECT_EQ(eventid.toString(), "$39hvsi03hlne:example.com");
        EXPECT_EQ(eventid.localpart(), "39hvsi03hlne");
        EXPECT_EQ(eventid.hostname(), "example.com");
}

TEST(MatrixIdentifiers, EventInValidHostname)
{
        ASSERT_THROW(parse<Event>("$39hvsi03hlne:com:109999"), std::invalid_argument);
}

TEST(MatrixIdentifiers, EventValidPort)
{
        Event eventid = parse<Event>("$39hvsi03hlne:example.com:5000");

        EXPECT_EQ(eventid.toString(), "$39hvsi03hlne:example.com:5000");
        EXPECT_EQ(eventid.localpart(), "39hvsi03hlne");
        EXPECT_EQ(eventid.hostname(), "example.com");
        EXPECT_EQ(eventid.port(), 5000);
}

TEST(MatrixIdentifiers, EventInValidPort)
{
        ASSERT_THROW(parse<Event>("$39hvsi03hlne:example.com:109999"), std::invalid_argument);
        ASSERT_THROW(parse<Event>("$39hvsi03hlne:example.com:-222"), std::invalid_argument);
}

TEST(MatrixIdentifiers, RoomValid)
{
        Room room1 = parse<Room>("!39fasdsdfsdf:example.com:5000");

        EXPECT_EQ(room1.toString(), "!39fasdsdfsdf:example.com:5000");
        EXPECT_EQ(room1.localpart(), "39fasdsdfsdf");
        EXPECT_EQ(room1.hostname(), "example.com");
        EXPECT_EQ(room1.port(), 5000);

        Room room2 = parse<Room>("!39fasdsdfsdf:example.com");

        EXPECT_EQ(room2.toString(), "!39fasdsdfsdf:example.com");
        EXPECT_EQ(room2.localpart(), "39fasdsdfsdf");
        EXPECT_EQ(room2.hostname(), "example.com");
        EXPECT_EQ(room2.port(), -1);
}

TEST(MatrixIdentifiers, IdentifierInvalid)
{
        ASSERT_THROW(parse<Room>("39fasdsdfsdf:example.com:5000"), std::invalid_argument);
        ASSERT_THROW(parse<Room>("!example.com:5000"), std::invalid_argument);
        ASSERT_THROW(parse<Room>(""), std::invalid_argument);
        ASSERT_THROW(parse<Room>("!test:matrix"), std::invalid_argument);

        ASSERT_THROW(parse<User>("39fasdsdfsdf:example.com:5000"), std::invalid_argument);
        ASSERT_THROW(parse<User>("!example.com:5000"), std::invalid_argument);
        ASSERT_THROW(parse<User>(""), std::invalid_argument);
        ASSERT_THROW(parse<User>("!test:matrix"), std::invalid_argument);
}
