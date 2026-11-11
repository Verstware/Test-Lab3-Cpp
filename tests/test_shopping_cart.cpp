#include <gtest/gtest.h>
#include "shopping_cart.cpp"

TEST(ShoppingCartTest, AddItemSuccess) {
    Product product("prod_1", "Смартфон", 50000.0, 10);
    ShoppingCart cart;
    cart.add_item(product, 2);
    EXPECT_EQ(cart.items["prod_1"].quantity, 2);
}

TEST(ShoppingCartTest, AddItemInvalidQuantity) {
    Product product("prod_1", "Смартфон", 50000.0, 10);
    ShoppingCart cart;
    EXPECT_THROW(cart.add_item(product, 0), std::invalid_argument);
    EXPECT_THROW(cart.add_item(product, -1), std::invalid_argument);
}

TEST(ShoppingCartTest, AddItemExceedStock) {
    Product product("prod_1", "Смартфон", 50000.0, 5);
    ShoppingCart cart;
    EXPECT_THROW(cart.add_item(product, 6), std::runtime_error);
}

TEST(ShoppingCartTest, RemoveItem) {
    Product product("prod_1", "Смартфон", 50000.0, 10);
    ShoppingCart cart;
    cart.add_item(product, 5);
    cart.remove_item("prod_1", 2);
    EXPECT_EQ(cart.items["prod_1"].quantity, 3);
    cart.remove_item("prod_1");
    EXPECT_EQ(cart.items.count("prod_1"), 0);
}

TEST(ShoppingCartTest, TotalPriceAndPromo) {
    Product product1("prod_1", "Товар 1", 100.0, 10);
    Product product2("prod_2", "Товар 2", 200.0, 10);
    ShoppingCart cart;
    cart.add_item(product1, 2);
    cart.add_item(product2, 1);
    EXPECT_DOUBLE_EQ(cart.get_total_price(), 400.0);
    cart.apply_promo("DISCOUNT10");
    EXPECT_DOUBLE_EQ(cart.get_total_price(), 360.0);
    EXPECT_THROW(cart.apply_promo("WRONGCODE"), std::invalid_argument);
}