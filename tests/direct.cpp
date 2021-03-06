#include "main.h"

TEST_CASE("DirectMode") {
  struct ncdirect* nc_ = ncdirect_init(NULL, stderr);
  if(!nc_){
    return;
  }

  SUBCASE("SetItalic") {
    CHECK(0 == ncdirect_styles_set(nc_, NCSTYLE_ITALIC));
    printf("DirectMode *italic*!\n");
    fflush(stdout);
    CHECK(0 == ncdirect_styles_off(nc_, NCSTYLE_ITALIC));
  }

  SUBCASE("SetBold") {
    CHECK(0 == ncdirect_styles_set(nc_, NCSTYLE_BOLD));
    printf("DirectMode *bold*!\n");
    fflush(stdout);
    CHECK(0 == ncdirect_styles_off(nc_, NCSTYLE_BOLD));
  }

  SUBCASE("SetUnderline") {
    CHECK(0 == ncdirect_styles_set(nc_, NCSTYLE_UNDERLINE));
    printf("DirectMode *underline*!\n");
    fflush(stdout);
    CHECK(0 == ncdirect_styles_off(nc_, NCSTYLE_UNDERLINE));
  }

  CHECK(0 == ncdirect_stop(nc_));
}
