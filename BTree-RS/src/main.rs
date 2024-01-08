use std::fmt::Debug;

#[derive(Debug)]
struct TreeNode<T>
    where T: Debug {
    pub value: T,
    left: Option<Box<TreeNode<T>>>,
    right: Option<Box<TreeNode<T>>>
}

impl<T: Debug + PartialOrd> TreeNode<T> {
    pub const fn new(value: T, left: Option<Box<Self>>, right: Option<Box<Self>>) -> Self {
        Self { value, left, right }
    }

    pub fn insert(value: T, root: &mut TreeNode<T>) {

        if value > root.value {
            match root.right {
                Some(ref mut right) => {
                    Self::insert(value, right);
                },
                None => {
                    root.right = Some(Box::new(TreeNode::new(value, None, None)));
                }
            }
        } else {
            match root.left {
                Some(ref mut left) => {
                    Self::insert(value, left);
                },
                None => {
                    root.left = Some(Box::new(TreeNode::new(value, None, None)));
                }
            }
        }
    }

    pub fn delete(value: T, root: &mut TreeNode<T>) {

        if root.value == value {
            TreeNode::replace_node_with_successor(root);
            return;
        }

        let child = if root.value < value { &mut root.right } else { &mut root.left };

        if !child.is_none() {
            TreeNode::remove_child(value, child)
        }
    }

    fn remove_child(value: T, child_node: &mut Option<Box<TreeNode<T>>>) {

        if let Some(ref mut child_node) = *child_node {

            if child_node.value != value {
                let new_child = if child_node.value < value { &mut child_node.right } else { &mut child_node.left };
                TreeNode::remove_child(value, new_child);
                return;
            }
        }

        TreeNode::remove_node(child_node);
    }

    fn remove_node(node: &mut Option<Box<TreeNode<T>>>) {

        if let Some(ref mut inner_node) = *node {

            if inner_node.left.is_none() && inner_node.right.is_none() {
                *node = None;
            } else if inner_node.left.is_some() && inner_node.right.is_none() {
                *node = inner_node.left.take();
            } else if inner_node.left.is_none() && inner_node.right.is_some() {
                *node = inner_node.right.take();
            } else {
                TreeNode::replace_node_with_successor(inner_node);
            }
        }
    }

    fn replace_node_with_successor(node: &mut TreeNode<T>) {


    }

}

fn main() {
    println!("Hello, world!");
}
