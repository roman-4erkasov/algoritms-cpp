#include"tree.h"

std::vector<int> tree::get_code(char value) {
  std::map<char, std::shared_ptr<node> >::iterator found = leaves.find(value);
  std::vector<int> result = std::vector<int>();
  if (found == leaves.end()) {
    std::cout << "\nERR:tree:get_code: value not found\n";
    return result;
  }
  std::shared_ptr<node> curr = found->second;
  while (curr && curr->parent.lock())
  {
    if (curr->parent.lock()->left&&curr == curr->parent.lock()->left)result.push_back(0);
    else if (curr->parent.lock()->right&&curr == curr->parent.lock()->right)result.push_back(1);
    curr = curr->parent.lock();
  }
  std::reverse(result.begin(), result.end());
  return result;
}

int tree::get_value(std::vector<int> code) {
  std::shared_ptr<node> curr = root;
  bool is_break = false;
  std::vector<int>::iterator it = code.begin();

  if (!curr) {
    std::cout << "\nWARN:tree:get_value: empty root\n";
    return ERR;
  }

  while ((it != code.end()) && (curr->left || curr->right))
  {
    if (*it != 0 && *it != 1) {
      std::cout << "\nERR:tree:get_value: only 0 or 1\n";
      return ERR;
    }

    if (*it == 0 && curr->left) {
      curr = curr->left;
      it++;
    }
    else if (*it == 1 && curr->right) {
      curr = curr->right;
      it++;
    }
    else
    {
      std::cout << "\nERR:tree:get_value: no such code\n";
      return ERR;
    }
  }
  return curr->value;
}

void tree::print_tree() {
  std::vector<std::shared_ptr<node> > stack = std::vector<std::shared_ptr<node> >();
  if (!root) {
    std::cout << "WARN:tree:print_tree: root empty";
  }
  stack.push_back(root);
  while (stack.size())
  {
    std::shared_ptr<node> curr = stack.back();
    stack.pop_back();
    //вывод
    int d = curr->deep();
    for (int i = 0; i < d; i++) {
      std::cout << '-';
    }
    std::cout << curr->to_string();

    if (curr!=nullptr) {
      if (curr->right!=nullptr)stack.push_back(curr->right);
      if (curr->left!=nullptr)stack.push_back(curr->left);
    }
  }
}

void tree::write_tree(std::ofstream &out) {
  typedef std::map<char, int>::iterator ittype;

  for (ittype it = frq.begin(); it != frq.end(); it++)
    out << static_cast<char>(it->first) << it->second << '\n';
  out << '\0' << 0 << '\n';
}

void tree::read_tree(std::ifstream &in) {
  typedef std::map<char, int>::iterator ittype;

  char ch = '\0';
  int num = 0;

  do {
    in.get(ch);
    in >> num;
    in.get();
    if (!(ch == '\0'&&num == 0)) {
      frq[ch] = num;
    }
  } while (!(ch == '\0'&&num == 0));

  if(frq.size()>0)create();
}

void tree::create() {
  typedef std::priority_queue<std::shared_ptr<node>, std::vector<std::shared_ptr<node> >, cmp> pqtype;
  pqtype pq = pqtype();

  for (std::map<char, int>::iterator it = frq.begin(); it != frq.end(); it++) {
    if (it->second>0)
    {
      std::shared_ptr<node> nd = std::shared_ptr<node> (new node(it->first, it->second, nullptr, nullptr, nullptr));
      leaves[nd->value] = nd;
      pq.push(nd);
    }
  }

  while (pq.size()>1)
  {
    std::shared_ptr<node> left = pq.top(); pq.pop();
    std::shared_ptr<node> right = pq.top(); pq.pop();
    std::shared_ptr<node> prnt = std::shared_ptr<node> (new node(INCOMPLETE_CD, left->weight + right->weight, nullptr, left, right));
    left->parent = right->parent = prnt;//неявная инициализация weak_ptr
    pq.push(prnt);
  }
  //каждыйкод будет начинаться с 1, т.к. укорня есть только правый потомок
  root= std::shared_ptr<node>(new node(INCOMPLETE_CD, pq.top()->weight, nullptr, nullptr, pq.top()));
  pq.top()->parent = root;
  pq.pop();
}
