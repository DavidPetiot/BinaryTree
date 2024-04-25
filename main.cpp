#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

enum Mode { pre_order = 0, in_order = 1, post_order = 2, level_order = 3 };

struct Tree {
  int m_node;
  Tree *m_left{nullptr};
  Tree *m_right{nullptr};
  int m_level{0};

  Tree(int val, int level = 0) : m_node(val), m_level(level) {}

  int insert(int val) {
    if (val < m_node) {
      if (m_left) {
        return m_left->insert(val);
      } else {
        m_left = new Tree(val, m_level + 1);
        return m_level + 1;
      }
    } else {
      if (m_right) {
        return m_right->insert(val);
      } else {
        m_right = new Tree(val, m_level + 1);
        return m_level + 1;
      }
    }
  }

  string ouput(int mode) {
    string left_str{""}, right_str{""}, node_str{to_string(m_node) + " "};
    if (m_left != nullptr) {
      left_str = m_left->ouput(mode);
    }

    if (m_right != nullptr) {
      right_str = m_right->ouput(mode);
    }

    switch (mode) {
    case pre_order:
      return node_str + left_str + right_str;
    case in_order:
      return left_str + node_str + right_str;
    case post_order:
      return left_str + right_str + node_str;
    default:
      return "unknown";
    }
  }
};

string output_level_order(Tree *tree, int level) {
  if (tree == nullptr)
    return "";
  else if (tree->m_level == level) {
    return to_string(tree->m_node) + " ";
  } else {
    return output_level_order(tree->m_left, level) +
           output_level_order(tree->m_right, level);
  }
}

int main() {
  int n;
  cin >> n;
  cin.ignore();
  vector<int> vec;
  for (int i = 0; i < n; i++) {
    int vi;
    cin >> vi;
    cin.ignore();
    vec.push_back(vi);
  }

  int max_depth{0};
  Tree tree(vec.front());

  for (int i = 1; i < vec.size(); i++) {
    max_depth = max(tree.insert(vec.at(i)), max_depth);
  }

  // pre-order, in-order, post-order
  for (int i = 0; i < 3; i++) {
    string str = tree.ouput(i);
    str.resize(str.size() - 1);
    cout << str << endl;
  }

  // level-order
  string temp{""};
  for (int i = 0; i <= max_depth; i++)
    temp += output_level_order(&tree, i);
  temp.resize(temp.size() - 1);
  cout << temp << endl;
}
