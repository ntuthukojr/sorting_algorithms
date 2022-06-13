#include "sort.h"
#include <stdio.h>

void swap_node(listint_t **list, listint_t *node1, listint_t *node2);
/**
 * cocktail_sort_list - a function to sort a linked list with a back and
 * forth max - min algorithmic approach. Max values will be bubbled up
 * with their node swapping to the correct place in the list while min
 * values will be bubbled down to their place.
 * @list: a doubly linked list with integer values as node->n
 * Return: Always void, it's pointers!
 */

void cocktail_sort_list(listint_t **list)
{
	listint_t *mover, *bubble_up, *bubble_down;
	int start = 0, end = 0, moving = 0, sort = 1, min, max;

	if (!list || !(*list) || !(*list)->next)
		return; /*This to check we have a valid list*/
	mover = *list; /*Set mover to head*/
	while (mover->next != NULL)
	{
		mover = mover->next;
		end++;
		if (mover->prev->n > mover->n)
			sort = 0; /*This is to check our list is un-ordered*/
	}
	if (sort == 1)
		return;/*If list is sorted, we done!*/
	mover = (*list);/*Reset mover to head*/
	while (start < end)
	{
		max = mover->n;/*Max is the first int for now*/
		while (moving < end)/*end is an int acting as a limit*/
		{
			mover = mover->next;
			if (mover->n > max)
			{
				max = mover->n; /*If currect n is > max, reassign*/
				bubble_up = mover;/*New biggest node is now bubble up*/
			}
			else
			{ /* If bubble up is bigger that current now, swap*/
				swap_node(list, bubble_up, mover);
				mover = bubble_up;
				print_list(*list);
			}
			moving++; /*Counter increases*/
		}
		end--;/*If we get to here we will have bubble up the biggest*/
		min = mover->n; /*Set the min value to current node*/
		while (moving > start) /*Working back towards start*/
		{
			mover = mover->prev;
			if (mover->n < min)
			{/*If the current node->n is less than*/
				min = mover->n; /*reassign minimum*/
				bubble_down = mover;/*current now is now bubble down*/
			}
			else
			{/*If bubble down node is less than current swap*/
				swap_node(list, mover, bubble_down);
				print_list(*list);
				mover = bubble_down;
			}
			moving--;/*Decrement each round for movement*/
		}
		start++;/*We should have bubble down this rounds min so shring window*/
	}
}

/**
 * swap_node - a fucntion to swap two nodes in a doubly linked list
 * @list: a doubly linked list
 * @node1: the first node
 * @node2: the second node to be swapped
 * Return: void, no return
 */

void swap_node(listint_t **list, listint_t *node1, listint_t *node2)
{
	if (node1->prev != NULL)
		node1->prev->next = node2;
	else
		(*list) = node2;
	node2->prev = node1->prev;
	node1->prev = node2;
	if (node2->next != NULL)
		node2->next->prev = node1;
	node1->next = node2->next;
	node2->next = node1;
}
