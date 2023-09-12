#include <Arduino.h>
#include <unity.h>
#include "TFT_Gui.h"

TFT_eSPI tft;

void setUp(void)
{
    // set stuff up here
    Serial.begin(115200);
}

void tearDown(void)
{
    // clean stuff up here
}

void test_viewport_x_and_y_can_not_be_negative(void)
{
    GUI_Viewport vp = GUI_Viewport(-2, -5, 20, 40);
    TEST_ASSERT_EQUAL(0, vp.position.x);
    TEST_ASSERT_EQUAL(0, vp.position.y);
}

void test_get_abs_pos(void)
{
    int parent_pos = 0;
    int parent_size = 100;
    int child_pos = 10;
    TEST_ASSERT_EQUAL(10, get_abs_pos(parent_pos, parent_size, child_pos));

    parent_pos = 25;
    child_pos = 10;
    TEST_ASSERT_EQUAL(35, get_abs_pos(parent_pos, parent_size, child_pos));

    parent_pos = 80;
    child_pos = 30;
    TEST_ASSERT_EQUAL(110, get_abs_pos(parent_pos, parent_size, child_pos));

    parent_pos = 0;
    child_pos = 130;
    TEST_ASSERT_EQUAL(100, get_abs_pos(parent_pos, parent_size, child_pos));
}

void test_get_abs_size(void)
{
    int parent_size = 100;

    int child_size = 20;
    int child_pos = 0;
    TEST_ASSERT_EQUAL(20, get_abs_size(parent_size, child_pos, child_size));

    child_size = 120;
    child_pos = 0;
    TEST_ASSERT_EQUAL(100, get_abs_size(parent_size, child_pos, child_size));

    child_size = -1;
    child_pos = 0;
    TEST_ASSERT_EQUAL(100, get_abs_size(parent_size, child_pos, child_size));

    child_size = -1;
    child_pos = 20;
    TEST_ASSERT_EQUAL(80, get_abs_size(parent_size, child_pos, child_size));
}

void test_viewport_get_absolute_viewport_from_bigger_parent(void)
{
    GUI_Viewport vp = GUI_Viewport(0, 0, 20, 40);
    GUI_Viewport abs = vp.getAbsoluteViewport(GUI_Viewport(0, 0, 30, 50));
    TEST_ASSERT_EQUAL(0, abs.position.x);
    TEST_ASSERT_EQUAL(0, abs.position.y);
    TEST_ASSERT_EQUAL(20, abs.size.w);
    TEST_ASSERT_EQUAL(40, abs.size.h);
}

void test_viewport_get_absolute_viewport_from_smaller_parent(void)
{
    GUI_Viewport vp = GUI_Viewport(0, 0, 20, 40);
    GUI_Viewport abs = vp.getAbsoluteViewport(GUI_Viewport(0, 0, 10, 35));
    TEST_ASSERT_EQUAL(0, abs.position.x);
    TEST_ASSERT_EQUAL(0, abs.position.y);
    TEST_ASSERT_EQUAL(10, abs.size.w);
    TEST_ASSERT_EQUAL(35, abs.size.h);
}

void test_viewport_get_absolute_viewport_with_auto_size(void)
{
    GUI_Viewport vp = GUI_Viewport(0, 0, -1, -1);
    GUI_Viewport abs = vp.getAbsoluteViewport(GUI_Viewport(0, 0, 10, 35));
    TEST_ASSERT_EQUAL(0, abs.position.x);
    TEST_ASSERT_EQUAL(0, abs.position.y);
    TEST_ASSERT_EQUAL(10, abs.size.w);
    TEST_ASSERT_EQUAL(35, abs.size.h);
}

void test_viewport_get_absolute_viewport_from_bigger_parent_with_offset(void)
{
    GUI_Viewport vp = GUI_Viewport(20, 10, 20, 40);
    GUI_Viewport abs = vp.getAbsoluteViewport(GUI_Viewport(0, 0, 30, 50));
    TEST_ASSERT_EQUAL(20, abs.position.x);
    TEST_ASSERT_EQUAL(10, abs.position.y);
    TEST_ASSERT_EQUAL(10, abs.size.w);
    TEST_ASSERT_EQUAL(40, abs.size.h);
}

void test_viewport_get_absolute_viewport_from_smaller_parent_with_offset(void)
{
    GUI_Viewport vp = GUI_Viewport(10, 10, 30, 40);
    GUI_Viewport abs = vp.getAbsoluteViewport(GUI_Viewport(0, 0, 20, 35));
    TEST_ASSERT_EQUAL(10, abs.position.x);
    TEST_ASSERT_EQUAL(10, abs.position.y);
    TEST_ASSERT_EQUAL(10, abs.size.w);
    TEST_ASSERT_EQUAL(25, abs.size.h);
}

void test_viewport_get_absolute_viewport_with_auto_size_with_offset(void)
{
    GUI_Viewport vp = GUI_Viewport(10, 10, -1, -1);
    GUI_Viewport abs = vp.getAbsoluteViewport(GUI_Viewport(0, 0, 20, 35));
    TEST_ASSERT_EQUAL(10, abs.position.x);
    TEST_ASSERT_EQUAL(10, abs.position.y);
    TEST_ASSERT_EQUAL(10, abs.size.w);
    TEST_ASSERT_EQUAL(25, abs.size.h);
}

// void test_gui_screen_create_without_background_color(void)
// {
//     GUI screen(&tft);
//     TEST_ASSERT_EQUAL(TFT_BLACK, screen.getBackgroundColor());
// }

// void test_gui_screen_create_with_background_color(void)
// {
//     GUI screen(&tft, TFT_BLUE);
//     TEST_ASSERT_EQUAL(TFT_BLUE, screen.getBackgroundColor());
// }

// void test_gui_screen_init(void)
// {
//     GUI screen(&tft, TFT_BLUE);
//     screen.init();
//     TEST_ASSERT_EQUAL(320, screen.absolute_viewport.size.w);
//     TEST_ASSERT_EQUAL(240, screen.absolute_viewport.size.h);
// }

// void test_gui_screen_set_background_color(void)
// {
//     GUI screen(&tft, TFT_BLUE);
//     TEST_ASSERT_EQUAL(TFT_BLUE, screen.getBackgroundColor());
//     screen.setBackgroundColor(TFT_RED);
//     TEST_ASSERT_EQUAL(TFT_RED, screen.getBackgroundColor());
// }

// void test_gui_page_create_without_background_color(void)
// {
//     GUI_Page page(&tft);
//     TEST_ASSERT_EQUAL(TFT_BLACK, page.getBackgroundColor());
// }

void test_gui_base_create_empty(void)
{
    GUI_Base base;
    TEST_ASSERT_EQUAL(GUI_itemType::BASE, base.itemType);
    TEST_ASSERT_EQUAL(-1, base.getObjectIndex());
    TEST_ASSERT_EQUAL(nullptr, base._parent);
    TEST_ASSERT_EQUAL(nullptr, base._sibling);
    TEST_ASSERT_EQUAL(nullptr, base._child);
    TEST_ASSERT_EQUAL(nullptr, base._tft);
    TEST_ASSERT_EQUAL(0, base.viewport.position.x);
    TEST_ASSERT_EQUAL(0, base.viewport.position.y);
    TEST_ASSERT_EQUAL(-1, base.viewport.size.w);
    TEST_ASSERT_EQUAL(-1, base.viewport.size.h);
    TEST_ASSERT_EQUAL(nullptr, base.getTFT());
    TEST_ASSERT_EQUAL(true, base.getVisible());
}

void test_gui_base_create_with_viewport(void)
{
    GUI_Base gui_base(GUI_Viewport(1, 2, 10, 20));
    TEST_ASSERT_EQUAL(nullptr, gui_base._parent);
    TEST_ASSERT_EQUAL(nullptr, gui_base._sibling);
    TEST_ASSERT_EQUAL(nullptr, gui_base._child);
    TEST_ASSERT_EQUAL(1, gui_base.viewport.position.x);
    TEST_ASSERT_EQUAL(2, gui_base.viewport.position.y);
    TEST_ASSERT_EQUAL(10, gui_base.viewport.size.w);
    TEST_ASSERT_EQUAL(20, gui_base.viewport.size.h);
}

void test_gui_base_hide(void)
{
    GUI_Base gui_base;
    TEST_ASSERT_EQUAL(true, gui_base.getVisible());
    gui_base.setVisible(false);
    TEST_ASSERT_EQUAL(false, gui_base.getVisible());
}

void test_gui_container_create_empty(void)
{
    GUI_Container container;
    TEST_ASSERT_EQUAL(GUI_itemType::CONTAINER, container.itemType);
    TEST_ASSERT_EQUAL(-1, container.getObjectIndex());
    TEST_ASSERT_EQUAL(nullptr, container._parent);
    TEST_ASSERT_EQUAL(nullptr, container._sibling);
    TEST_ASSERT_EQUAL(nullptr, container._child);
    TEST_ASSERT_EQUAL(nullptr, container._tft);
    TEST_ASSERT_EQUAL(0, container.viewport.position.x);
    TEST_ASSERT_EQUAL(0, container.viewport.position.y);
    TEST_ASSERT_EQUAL(-1, container.viewport.size.w);
    TEST_ASSERT_EQUAL(-1, container.viewport.size.h);
    TEST_ASSERT_EQUAL(nullptr, container.getTFT());
    TEST_ASSERT_EQUAL(true, container.getVisible());
    TEST_ASSERT_EQUAL(0, container.getChildCount());
    TEST_ASSERT_EQUAL(0, container.getBackgroundColor());
}

void test_gui_container_create_with_background(void)
{
    GUI_Container container(TFT_BLUE);
    TEST_ASSERT_EQUAL(TFT_BLUE, container.getBackgroundColor());
}

void test_gui_container_create_with_viewport_and_background(void)
{
    GUI_Container container(GUI_Viewport(1, 2, 10, 20), TFT_BLUE);
    TEST_ASSERT_EQUAL(1, container.viewport.position.x);
    TEST_ASSERT_EQUAL(2, container.viewport.position.y);
    TEST_ASSERT_EQUAL(10, container.viewport.size.w);
    TEST_ASSERT_EQUAL(20, container.viewport.size.h);
    TEST_ASSERT_EQUAL(TFT_BLUE, container.getBackgroundColor());
}

void test_gui_container_set_background(void)
{
    GUI_Container container;
    TEST_ASSERT_EQUAL(0, container.getBackgroundColor());
    container.setBackgroundColor(TFT_BLUE);
    TEST_ASSERT_EQUAL(TFT_BLUE, container.getBackgroundColor());
}

void test_gui_container_add_child(void)
{
    GUI_Container container;
    GUI_Base child;
    container.addChild(&child);
    TEST_ASSERT_EQUAL(&child, container._child);
    TEST_ASSERT_EQUAL(1, container.getChildCount());
    TEST_ASSERT_EQUAL(0, child.getObjectIndex());
}

void test_gui_container_add_child_twice(void)
{
    GUI_Container container;
    GUI_Base child;
    container.addChild(&child);
    container.addChild(&child);
    TEST_ASSERT_EQUAL(&child, container._child);
    TEST_ASSERT_EQUAL(1, container.getChildCount());
    TEST_ASSERT_EQUAL(0, child.getObjectIndex());
}

void test_gui_container_add_two_children(void)
{
    GUI_Container container;
    GUI_Base child;
    GUI_Base child2;
    container.addChild(&child);
    TEST_ASSERT_EQUAL(&child, container._child);
    TEST_ASSERT_EQUAL(1, container.getChildCount());
    TEST_ASSERT_EQUAL(0, child.getObjectIndex());
    container.addChild(&child2);
    TEST_ASSERT_EQUAL(2, container.getChildCount());
    TEST_ASSERT_EQUAL(1, child2.getObjectIndex());
}

void test_screen_create_empty(void)
{
    TFT_eSPI tft;
    GUI_Screen screen(&tft);
    TEST_ASSERT_EQUAL(GUI_itemType::SCREEN, screen.itemType);
    TEST_ASSERT_EQUAL(-1, screen.getObjectIndex());
    TEST_ASSERT_EQUAL(nullptr, screen._parent);
    TEST_ASSERT_EQUAL(nullptr, screen._sibling);
    TEST_ASSERT_EQUAL(nullptr, screen._child);
    TEST_ASSERT_EQUAL(&tft, screen._tft);
    TEST_ASSERT_EQUAL(0, screen.viewport.position.x);
    TEST_ASSERT_EQUAL(0, screen.viewport.position.y);
    TEST_ASSERT_EQUAL(-1, screen.viewport.size.w);
    TEST_ASSERT_EQUAL(-1, screen.viewport.size.h);
    TEST_ASSERT_EQUAL(&tft, screen.getTFT());
    TEST_ASSERT_EQUAL(true, screen.getVisible());
    TEST_ASSERT_EQUAL(0, screen.getChildCount());

    // // TEST_ASSERT_EQUAL(nullptr, screen.first_page);
    // TEST_ASSERT_EQUAL(0, screen.pageCount());
    // TEST_ASSERT_EQUAL(-1, screen.getActivePage());
}

void test_screen_init(void)
{
    TFT_eSPI tft;
    GUI_Screen screen(&tft);
    TEST_ASSERT_EQUAL(0, screen.viewport.position.x);
    TEST_ASSERT_EQUAL(0, screen.viewport.position.y);
    TEST_ASSERT_EQUAL(-1, screen.viewport.size.w);
    TEST_ASSERT_EQUAL(-1, screen.viewport.size.h);
    screen.init();
    TEST_ASSERT_EQUAL(0, screen.viewport.position.x);
    TEST_ASSERT_EQUAL(0, screen.viewport.position.y);
    TEST_ASSERT_EQUAL(tft.width(), screen.viewport.size.w);
    TEST_ASSERT_EQUAL(tft.height(), screen.viewport.size.h);
    // // TEST_ASSERT_EQUAL(nullptr, screen.first_page);
    // TEST_ASSERT_EQUAL(0, screen.pageCount());
    // TEST_ASSERT_EQUAL(-1, screen.getActivePage());
}

void test_screen_add_child(void)
{
    TFT_eSPI tft;
    GUI_Screen screen(&tft);
    GUI_Base child;
    TEST_ASSERT_EQUAL(nullptr, child.getTFT());
    screen.addChild(&child);
    TEST_ASSERT_EQUAL(&child, screen._child);
    TEST_ASSERT_EQUAL(&tft, child.getTFT());
}

void test_screen_add_page_with_wrong_type(void)
{
    TFT_eSPI tft;
    GUI_Screen screen(&tft);
    GUI_Base child;
    screen.addPage(&child);
    TEST_ASSERT_EQUAL(nullptr, screen._child);
    TEST_ASSERT_EQUAL(0, screen.getChildCount());
    TEST_ASSERT_EQUAL(-1, child.getObjectIndex());
    TEST_ASSERT_EQUAL(-1, screen.getActivePage());
}

void test_screen_add_page(void)
{
    TFT_eSPI tft;
    GUI_Screen screen(&tft);
    GUI_Page child;
    TEST_ASSERT_EQUAL(GUI_itemType::PAGE, child.itemType);

    TEST_ASSERT_EQUAL(nullptr, child.getTFT());
    screen.addPage(&child);
    TEST_ASSERT_EQUAL(&child, screen._child);
    TEST_ASSERT_EQUAL(1, screen.getChildCount());
    TEST_ASSERT_EQUAL(&tft, child.getTFT());
    TEST_ASSERT_EQUAL(0, child.getObjectIndex());
    TEST_ASSERT_EQUAL(0, screen.getActivePage());
}

void test_screen_add_two_page(void)
{
    TFT_eSPI tft;
    GUI_Screen screen(&tft);
    GUI_Page child;
    GUI_Page child2;
    TEST_ASSERT_EQUAL(GUI_itemType::PAGE, child.itemType);
    TEST_ASSERT_EQUAL(nullptr, child.getTFT());
    screen.addPage(&child);
    TEST_ASSERT_EQUAL(&child, screen._child);
    TEST_ASSERT_EQUAL(1, screen.getChildCount());
    TEST_ASSERT_EQUAL(&tft, child.getTFT());
    TEST_ASSERT_EQUAL(0, child.getObjectIndex());
    TEST_ASSERT_EQUAL(0, screen.getActivePage());
    screen.addPage(&child2);
    TEST_ASSERT_EQUAL(&child, screen._child);
    TEST_ASSERT_EQUAL(2, screen.getChildCount());
    TEST_ASSERT_EQUAL(&tft, child2.getTFT());
    TEST_ASSERT_EQUAL(1, child2.getObjectIndex());
    TEST_ASSERT_EQUAL(0, screen.getActivePage());
}
void test_gui_page_create_empty(void)
{
    GUI_Page page;
    TEST_ASSERT_EQUAL(GUI_itemType::PAGE, page.itemType);
    TEST_ASSERT_EQUAL(-1, page.getObjectIndex());
    TEST_ASSERT_EQUAL(nullptr, page._parent);
    TEST_ASSERT_EQUAL(nullptr, page._sibling);
    TEST_ASSERT_EQUAL(nullptr, page._child);
    TEST_ASSERT_EQUAL(nullptr, page._tft);
    TEST_ASSERT_EQUAL(0, page.viewport.position.x);
    TEST_ASSERT_EQUAL(0, page.viewport.position.y);
    TEST_ASSERT_EQUAL(-1, page.viewport.size.w);
    TEST_ASSERT_EQUAL(-1, page.viewport.size.h);
    TEST_ASSERT_EQUAL(nullptr, page.getTFT());
    TEST_ASSERT_EQUAL(true, page.getVisible());
    TEST_ASSERT_EQUAL(TFT_BLACK, page.getBackgroundColor());
}

void test_gui_page_create_with_background(void)
{
    GUI_Page page;
    TEST_ASSERT_EQUAL(GUI_itemType::PAGE, page.itemType);
    TEST_ASSERT_EQUAL(-1, page.getObjectIndex());
    TEST_ASSERT_EQUAL(nullptr, page._parent);
    TEST_ASSERT_EQUAL(nullptr, page._sibling);
    TEST_ASSERT_EQUAL(nullptr, page._child);
    TEST_ASSERT_EQUAL(nullptr, page._tft);
    TEST_ASSERT_EQUAL(0, page.viewport.position.x);
    TEST_ASSERT_EQUAL(0, page.viewport.position.y);
    TEST_ASSERT_EQUAL(-1, page.viewport.size.w);
    TEST_ASSERT_EQUAL(-1, page.viewport.size.h);
    TEST_ASSERT_EQUAL(nullptr, page.getTFT());
    TEST_ASSERT_EQUAL(true, page.getVisible());
    TEST_ASSERT_EQUAL(TFT_BLACK, page.getBackgroundColor());
}

// void test_gui_page_set_index(void)
// {
//     GUI_Page page;
//     page.setPageIndex(5);
//     TEST_ASSERT_EQUAL(5, page.getPageIndex());
// }

// void test_gui_page_create_with_background_color(void)
// {
//     GUI_Page page(TFT_RED);
//     TEST_ASSERT_EQUAL(TFT_RED, page.getBackgroundColor());
// }

// void test_gui_page_set_background_color(void)
// {
//     GUI_Page page(TFT_RED);
//     TEST_ASSERT_EQUAL(TFT_RED, page.getBackgroundColor());
//     page.setBackgroundColor(TFT_BLUE);
//     TEST_ASSERT_EQUAL(TFT_BLUE, page.getBackgroundColor());
// }

// // test_gui_page_create(void)
// // test_gui_form_create(void)
// // test_gui_label_create(void)

void test_gui_page_absolute_viewport(void)
{
    TFT_eSPI tft;
    GUI_Screen screen(&tft);
    screen.init();
    GUI_Page page_1;
    screen.addPage(&page_1);
    TEST_ASSERT_EQUAL(tft.width(), page_1.getAbsoluteViewport().size.w);
    TEST_ASSERT_EQUAL(tft.height(), page_1.getAbsoluteViewport().size.h);
}

void test_gui_value_int(void)
{
    GUI_Value value(GUI_Viewport(230, 170, 50, 30), TFT_BLACK, FF17, BR_DATUM, 0, 0);
    TEST_ASSERT_EQUAL(0, value.getValue());
    TEST_ASSERT_EQUAL(true, value.getPrintValue().equals("0"));
    value.updateValue(10);
    TEST_ASSERT_EQUAL(10, value.getValue());
    value.updateValue(float(30.5));
    TEST_ASSERT_EQUAL(30, value.getValue());
}

void test_gui_value_float(void)
{
    GUI_Value value(GUI_Viewport(230, 170, 50, 30), TFT_BLACK, FF17, BR_DATUM, 2, 0);
    TEST_ASSERT_EQUAL(0, value.getValue());
    TEST_ASSERT_EQUAL(true, value.getPrintValue().equals("0.00"));
    value.updateValue(1.23, 3);
    TEST_ASSERT_EQUAL(true, value.getPrintValue().equals("1.230"));
}

// void test_gui_select_pages(void)
// {
//     GUI_Screen gui(&tft);
//     GUI_Page page_1;
//     GUI_Page page_2;
//     TEST_ASSERT_EQUAL(1, gui.addPage(&page_1));
//     TEST_ASSERT_EQUAL(2, gui.addPage(&page_2));
//     TEST_ASSERT_EQUAL(0, gui.getActivePage());
//     gui.setActivePage(1);
//     TEST_ASSERT_EQUAL(1, gui.getActivePage());
//     gui.setActivePage(0);
//     TEST_ASSERT_EQUAL(0, gui.getActivePage());
// }

// test_gui_add_label_to_form(void)
// test_gui_add_label_to_page(void)
void setup()
{
    delay(2000); // service delay
    UNITY_BEGIN();

    RUN_TEST(test_viewport_x_and_y_can_not_be_negative);
    RUN_TEST(test_get_abs_pos);
    RUN_TEST(test_get_abs_size);
    RUN_TEST(test_viewport_get_absolute_viewport_from_bigger_parent);
    RUN_TEST(test_viewport_get_absolute_viewport_from_smaller_parent);
    RUN_TEST(test_viewport_get_absolute_viewport_with_auto_size);
    RUN_TEST(test_viewport_get_absolute_viewport_from_bigger_parent_with_offset);
    RUN_TEST(test_viewport_get_absolute_viewport_from_smaller_parent_with_offset);
    RUN_TEST(test_viewport_get_absolute_viewport_with_auto_size_with_offset);

    RUN_TEST(test_gui_base_create_empty);
    RUN_TEST(test_gui_base_create_with_viewport);

    RUN_TEST(test_gui_container_create_empty);
    RUN_TEST(test_gui_container_create_with_background);
    RUN_TEST(test_gui_container_create_with_viewport_and_background);
    RUN_TEST(test_gui_container_set_background);
    RUN_TEST(test_gui_container_add_child);
    RUN_TEST(test_gui_container_add_child_twice);
    RUN_TEST(test_gui_container_add_two_children);

    RUN_TEST(test_screen_create_empty);

    RUN_TEST(test_screen_add_child);

    RUN_TEST(test_screen_init);

    RUN_TEST(test_gui_page_create_empty);

    RUN_TEST(test_screen_add_page_with_wrong_type);

    RUN_TEST(test_screen_add_page);
    RUN_TEST(test_screen_add_two_page);

    RUN_TEST(test_gui_page_absolute_viewport);
    RUN_TEST(test_gui_value_int);
    RUN_TEST(test_gui_value_float);

    // RUN_TEST(test_gui_add_page);
    // RUN_TEST(test_gui_add_same_page_twice);
    // RUN_TEST(test_gui_add_two_pages);

    // RUN_TEST(test_gui_select_pages);

    // RUN_TEST();
    // RUN_TEST();
    // RUN_TEST();
    // RUN_TEST();
    // RUN_TEST();
    // RUN_TEST();
    // RUN_TEST();
    // RUN_TEST();

    UNITY_END(); // stop unit testing
}

void loop()
{
}