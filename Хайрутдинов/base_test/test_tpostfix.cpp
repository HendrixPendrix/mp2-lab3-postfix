#include "postfix.h"
#include <gtest.h>

TEST(TPostfix, can_create_postfix)
{
	ASSERT_NO_THROW(TPostfix p);
}
TEST(TPostfix, can_get_postfix_of_two_arguments_with_brackets)
{
	TPostfix p("(a+b)*c");
	p.ToPostfix();
	EXPECT_EQ("a b + c * ", p.GetPostfix());
}
TEST(TPostfix, can_get_postfix_of_two_arguments)
{
	TPostfix p("a+b");
	p.ToPostfix();
	EXPECT_EQ("a b + ", p.GetPostfix());
}
TEST(TPostfix, can_get_postfix_of_three_arguments)
{
	TPostfix p("a+b*c");
	p.ToPostfix();
	EXPECT_EQ("a b c * + ", p.GetPostfix());
}
TEST(TPostfix, can_set_infix)
{
	ASSERT_NO_THROW(TPostfix p("a+b"));
}
TEST(TPostfix, can_get_infix)
{
	TPostfix p("a+b");
	EXPECT_EQ("a+b", p.GetInfix());
}
TEST(TPostfix, can_get_postfix_with_different_operations)
{
	TPostfix p("a+b*c");
	p.ToPostfix();
	EXPECT_EQ("a b c * + ", p.GetPostfix());
}
TEST(TPostfix, can_get_postfix_with_closed_bracket)
{
	TPostfix p(")a+b");
	ASSERT_ANY_THROW(p.ToPostfix());
}
TEST(TPostfix, can_get_postfix_with_operation_in_begin)
{
	TPostfix p("*a+b)");
	ASSERT_ANY_THROW(p.ToPostfix());
}
TEST(TPostfix, cant_create_postfix_with_incorrect_infix)
{
	TPostfix p("a++b");
	ASSERT_ANY_THROW(p.ToPostfix());
}
TEST(TPostfix, can_calculate)
{
	ASSERT_NO_THROW(TPostfix p);
}
TEST(TPostfix, the_postfix_form_can_calculate_with_repeat_symbols)
{
	TPostfix str("2+3*2");
	str.ToPostfix();
	EXPECT_EQ(8, str.Calculate());
}
TEST(TPostfix, the_postfix_form_can_calculate_without_repeat_symbols)
{
	TPostfix str("2+3"); 
	str.ToPostfix();
	EXPECT_EQ(5, str.Calculate());
}