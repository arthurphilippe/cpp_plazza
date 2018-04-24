/*
** EPITECH PROJECT, 2018
** cpp_plazza
** File description:
** RegexScrapper
*/

#include "RegexScrapper.hpp"

using Plazza::RegexScrapper;

RegexScrapper::RegexScrapper(const std::string &patnern)
	: _regex(patnern)
{}

void RegexScrapper::run(const Command &)
{}

std::ostream &RegexScrapper::serialise(std::ostream &)
{}
