#pragma once
#include <string>
#include <unordered_map>
#include <stdexcept>

struct Product {
    std::string id;
    std::string name;
    double price;
    int stock;

    Product() = default;

    Product(std::string id, std::string name, double price, int stock)
        : id(std::move(id)), name(std::move(name)), price(price), stock(stock) {}
};

struct CartItem {
    Product product;
    int quantity = 0;
};

class ShoppingCart {
public:
    std::unordered_map<std::string, CartItem> items;
    double discount = 0.0;

    void add_item(const Product& product, int quantity) {
        if (quantity <= 0) {
            throw std::invalid_argument("Количество должно быть больше нуля");
        }

        int current_in_cart = 0;
        if (items.find(product.id) != items.end()) {
            current_in_cart = items[product.id].quantity;
        }

        int total_requested = current_in_cart + quantity;
        if (total_requested > product.stock) {
            throw std::runtime_error("Превышено доступное количество на складе");
        }

        if (items.find(product.id) != items.end()) {
            items[product.id].quantity = total_requested;
        } else {
            items[product.id] = {product, quantity};
        }
    }

    void remove_item(const std::string& product_id, int quantity = -1) {
        auto it = items.find(product_id);
        if (it == items.end()) {
            return;
        }

        if (quantity < 0 || quantity >= it->second.quantity) {
            items.erase(it);
        } else {
            it->second.quantity -= quantity;
        }
    }

    void apply_promo(const std::string& code) {
        if (code == "DISCOUNT10") {
            discount = 0.10;
        } else if (code == "DISCOUNT20") {
            discount = 0.20;
        } else {
            throw std::invalid_argument("Неверный промокод");
        }
    }

    double get_total_price() const {
        double total = 0.0;
        for (const auto& pair : items) {
            total += pair.second.product.price * pair.second.quantity;
        }
        return total * (1.0 - discount);
    }
};