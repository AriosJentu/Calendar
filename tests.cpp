#include "Calendar.cpp"
#include <gtest/gtest.h>

TEST(Test1, Test1Ex) {

	Calendar fst(31, 12, 1998);
	Calendar scd(1, 1, 1999);
	fst = fst + 1;

	ASSERT_EQ(fst.day, scd.day);
	ASSERT_EQ(fst.month, scd.month);
	ASSERT_EQ(fst.year, scd.year);
}

TEST(Test2, Test2Ex) {

	Calendar scd(1, 1, 1999);
	Calendar fst(31, 12, 1998);
	scd = scd-1;

	ASSERT_EQ(fst.day, scd.day);
	ASSERT_EQ(fst.month, scd.month);
	ASSERT_EQ(fst.year, scd.year);
}

TEST(Test3, Test3Ex) {

	Calendar fst(31, 12, 1998);
	Calendar scd(31, 12, 1999);
	fst = fst + 365;

	ASSERT_EQ(fst.day, scd.day);
	ASSERT_EQ(fst.month, scd.month);
	ASSERT_EQ(fst.year, scd.year);
}

TEST(Test4, Test4Ex) {

	Calendar fst(31, 12, 1998);
	Calendar scd(31, 12, 1999);
	int dif = fst-scd;

	ASSERT_EQ(dif, 365);
}

TEST(Test5, Test5Ex) {

	Calendar fst("31-12-1998");
	Calendar scd(31, 12, 1998);

	ASSERT_EQ(fst.day, scd.day);
	ASSERT_EQ(fst.month, scd.month);
	ASSERT_EQ(fst.year, scd.year);
}

TEST(Test6, Test6Ex) {

	Calendar fst("12-31-1998");
	Calendar scd(31, 12, 1998);

	ASSERT_EQ(fst.day, scd.day);
	ASSERT_EQ(fst.month, scd.month);
	ASSERT_EQ(fst.day, 31);
}

TEST(Test7, Test7Ex) {

	Calendar fst("1998-12-31");
	Calendar scd(31, 12, 1998);

	ASSERT_EQ(fst.day, scd.day);
	ASSERT_EQ(fst.month, scd.month);
	ASSERT_EQ(fst.year, scd.year);
}

TEST(Test8, Test8Ex) {

	ASSERT_THROW(Calendar("1998-13-31"), Calendar::Exception);
}

TEST(Test9, Test9Ex) {

	Calendar fst("12~16~2018");
	fst.setFormat("4Y2D2M:");

	std::string str = fst;

	ASSERT_EQ(str, "2018:16:12");
}

TEST(Test10, Test10Ex) {

	Calendar date1(21, 4, 2018);
	Calendar date2(22, 4, 2018);
	Calendar date3(23, 4, 2018);

	ASSERT_EQ(date1.getWeekDay(), 6); //21.04.2018 is satday (6)
	ASSERT_EQ(date2.getWeekDay(), 7); //22.04.2018 is sunday (7)
	ASSERT_EQ(date3.getWeekDay(), 1); //23.04.2018 is monday (1)

}

TEST(Test11, Test11Ex) {

	Calendar date1(21, 4, 2000);
	Calendar date2(21, 4, 2012);
	Calendar date3(21, 4, 2018);
	Calendar date4(21, 4, 2100);

	ASSERT_EQ(date1.isYearLeap(), true);
	ASSERT_EQ(date2.isYearLeap(), true);
	ASSERT_EQ(date3.isYearLeap(), false);
	ASSERT_EQ(date4.isYearLeap(), false);

}


int main(int argc, char** argv) {
	testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}