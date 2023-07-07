int countSongs(Song p)
{	
	int count = 0;
	while(p != NULL){
		count++;
		p = p->next;
	}
	return count;
}

AVLTree DoubleRotateWithRight(AVLTree k3)
{
	k3->right = SingleRotateWithLeft(k3->right);
	return SingleRotateWithRight(k3);
}

AVLTree DoubleRotateWithLeft(AVLTree k3)
{
	k3->left = SingleRotateWithRight(k3->left);
	return SingleRotateWithLeft(k3);
}

AVLTree SingleRotateWithRight(AVLTree k1)
{
	AVLTree k2;
	k2 = k1->right;
	k1->right = k2->left;
	k2->left = k1;

	k1->height = TreeHeight(k1);
	k2->height = TreeHeight(k2);

	return k2;
}

AVLTree SingleRotateWithLeft(AVLTree k2)
{
	AVLTree k1;
	k1 = k2->left;
	k2->left = k1->right;
	k1->right = k2;

	k2->height = TreeHeight(k2);
	k1->height = TreeHeight(k1);

	return k1;
}

int TreeHeight(AVLTree t)
{
	int l = 0, r = 0;
	if(t == NULL)
		return -1;
	else{
		//compute left side, then right side
		l = TreeHeight(t->left);
		r = TreeHeight(t->right);

		//use the larger one
		if(l > r)
			return (l + 1);
		else
			return (r + 1);
	}
}