#include "Tree.h"
#include "ItemCategory.h"
#include "EarleyItem.h"
#include "EarleyTable.h"
#include <iostream>
#include <fstream>


using namespace std;

Tree::Tree(EarleyTable& table)
	: table(table)
{

}

void Tree::parse_earley_table()
{
	

	string start_symbole = table.front().front().get_rule()->get_main_symbole();

	int i = table.back().get_index();
	Node* u0 = new Node(start_symbole, 0, i);
	u0->set_root(true);
	node_list.clear();
	node_list.push_back(*u0);

	for (EarleyItem& item : table.back().get_set())
		if (item.get_rule()->get_main_symbole() == start_symbole
			&&
			item.get_position() == item.get_rule()->get_body().size()
			&&
			item.get_item_start() == 0)
		{
			build_tree(u0, &item, i);
		}
}

void Tree::build_tree(Node* u, EarleyItem* p, int i)
{
	u = add_node_if_not_present(u);
	string A = p->get_rule()->get_main_symbole();
	int j = p->get_item_start();

	// mark p as processed
	p->mark_as_processed();

	// wich category of p ?
	ItemCategory category = table.get_category(p);

	// if p = (A :: . ,j)
	if (category.category == 1) {
		if (!u->has_family(&(get_epsilon())))
			u->add_family(&(get_epsilon()));
	}
		
	// if p = (A :: a . Beta ,j)
	else if (category.category == 2) {
		Node* v = new Node{ category.a, i - 1, i };
		v = add_node_if_not_present(v);
		if (!u->has_family(v))
			u->add_family(v);
	}
		
	// if p = (A :: C . Beta ,j)
	else if (category.category == 3) {
		Node *v = new Node{ category.C, j, i };
		v = add_node_if_not_present(v);
		if (!u->has_family(v))
			u->add_family(v);
		for (EarleyItemPtr& item_ptr : p->get_reduction_ptr_list().get_list()) {
			if (item_ptr.get_name() == j) {
				EarleyItem* q = item_ptr.get_item_ptr();
				if (q->is_not_processed())
					build_tree(v, q, i);
			}
		}
	}

	// if p = (A :: Alpha a . Beta ,j)
	else if (category.category == 4) {
		Node* v = new Node{ category.a, i - 1, i };
		v = add_node_if_not_present(v);

		string name = A + "::=" + category.alpha_prim + "." + category.a + p->get_beta();
		Node* w = new Node{ name, j, i - 1 };
		w = add_node_if_not_present(w);

		for (EarleyItemPtr& item_ptr : p->get_predecessor_ptr_list().get_list()) {
			if (item_ptr.get_name() == i - 1) {
				EarleyItem* p_prim = item_ptr.get_item_ptr();
				if (p_prim->is_not_processed())
					build_tree(w, p_prim, i - 1);
			}
		}

		if (!u->has_family(w, v))
			u->add_family(w, v);
	}

	// if p = (A :: Alpha C . Beta ,j)
	else if (category.category == 5) {
		for (EarleyItemPtr& item_ptr : p->get_reduction_ptr_list().get_list()) {
			int l = item_ptr.get_name();
		
			EarleyItem* q = item_ptr.get_item_ptr();
			
			Node* v = new Node{ category.C, l, i };
			v = add_node_if_not_present(v);

			if (q->is_not_processed())
				build_tree(v, q, i);
			
			string name = A + ":==" + category.alpha_prim + "." + category.C + p->get_beta();
			Node* w = new Node{ name, j, l };
			w = add_node_if_not_present(w);

			for (EarleyItemPtr& item_ptr : p->get_predecessor_ptr_list().get_list()) {
				if (item_ptr.get_name() == l) {
					EarleyItem* p_prim = item_ptr.get_item_ptr();
					if (p_prim->is_not_processed())
						build_tree(w, p_prim, l);
				}
			}

			if (!u->has_family(w, v))
				u->add_family(w, v);
		}
	}
}

Node * Tree::add_node_if_not_present(Node* node1)
{
	for (Node& node : node_list)
		if (node == *node1)
			return &node;
	
	node_list.push_back(*node1);
	return &(node_list.back());
}

Node & Tree::get_epsilon()
{
	return epsilon;
}

void Tree::print_tree()
{
	for (Node node : node_list) {
		if (node.is_root()) {
			node.print_tree();
		}
	}
}

void Tree::print_tree_in_dot_format(ostream & dot_file)
{
	dot_file << "digraph {" << "\n";
	for (Node node : node_list) {
		if (node.is_root()) {
			node.print_tree_in_dot_format(dot_file);
		}
	}
	dot_file << "}" << "\n";
}



