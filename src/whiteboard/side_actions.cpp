/* $Id$ */
/*
 Copyright (C) 2010 by Gabriel Morin <gabrielmorin (at) gmail (dot) com>
 Part of the Battle for Wesnoth Project http://www.wesnoth.org

 This program is free software; you can redistribute it and/or modify
 it under the terms of the GNU General Public License version 2
 or at your option any later version.
 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY.

 See the COPYING file for more details.
 */

/**
 * @file side_actions.cpp
 */

#include "side_actions.hpp"
#include "action.hpp"
#include "move.hpp"

namespace wb
{

side_actions::side_actions()
{
	// TODO Auto-generated constructor stub

}

side_actions::~side_actions()
{
	// TODO Auto-generated destructor stub
}

const action_set& side_actions::get_actions() const
{
	return actions_;
}

void side_actions::insert_move(unit& subject, const map_location& target_hex, arrow& arrow, size_t index)
{
	action_ptr action(new move(subject, target_hex, arrow));
	assert(index < end());
	actions_.insert(actions_.begin() + index, action);

}

void side_actions::queue_move(unit& subject, const map_location& target_hex, arrow& arrow)
{
	insert_move(subject, target_hex, arrow, end());
}

void side_actions::move_earlier(size_t index, size_t increment)
{
	move_in_queue(index, - (int) increment);
}

void side_actions::move_later(size_t index, size_t increment)
{
	move_in_queue(index, (int) increment);
}

void side_actions::remove_action(size_t index)
{
	assert(!actions_.empty());
	assert(index < end());

	action_set::iterator position = actions_.begin()+index;
	if (position < actions_.end())
	{
		actions_.erase(position);
	}
}

/*
 * Utility function to move actions around the queue.
 * Positive increment = move toward back of the queue and later execution.
 * Negative increment = move toward front of the queue and earlier execution.
 */
void side_actions::move_in_queue(size_t index, int increment)
{
	assert(!actions_.empty());
	assert(index < end());
	if (actions_.empty() || index >= end())
	{
		return;
	}

	action_set::iterator position;
	position = actions_.begin() + index;

	assert(index + increment < end());
	if (index + increment >= end())
	{
		increment = int(end()) - index;
	}

	assert(int(index) + increment >= 0);
	if (int(index) + increment < 0)
	{
		increment = -index;
	}

	action_ptr action = *position;
	action_set::iterator after = actions_.erase(position);
	//be careful, previous iterators have just been invalidated by erase()
	action_set::iterator destination = after + increment;
	actions_.insert(destination, action);
}


}
