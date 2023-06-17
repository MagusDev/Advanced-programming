#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <algorithm>

using namespace std;


void summary(vector<string> entry);
int countPositiveWords(string sentence, vector<string> PositiveWords);

int main()
{
	ifstream infile("positive-words.txt");
	string word;
	vector<string> positive_words;
	while(getline(infile,word))
	{
		positive_words.push_back(word);
	}
	
	/*
	infile.close();
	for(string word : positive_words)
	{
		cout<<word<<endl;
	}
	*/
	
	string inputLine;
	vector<pair<string,vector<string>>> diary;
	string command;
	string date;
	
	while(getline(cin,inputLine))
	{
		command =inputLine.substr(0, inputLine.find(' '));
	
		if(command == "start_day")
		{
			date = inputLine.substr(inputLine.find(' ') + 1);
			vector<string> entries;
			diary.push_back(make_pair(date,entries));
		}
		
		//show a specific entry completely
		else if(command == "show_day")
		{
			string seek_date = inputLine.substr(inputLine.find(' ') + 1);
			for(auto entry : diary)
			{
				if(entry.first == seek_date)
				{
					for(auto line : entry.second)
					{
						cout<<line<<endl;
					}
					break;
				}
			}
		}
		
		//show longest day command
		else if(command == "show_the_longest_day")
		{
			int highest_length = 0;
			int index = 0;
			
			for(unsigned int i = 0; i< diary.size();i++)
			{
				int entry_length = 0;
				for(auto line : diary[i].second)
					{
						entry_length += line.size();
					}
				if(entry_length > highest_length)
				{
					highest_length = entry_length;
					index = i;
				}
				
			}
			cout<<diary[index].first<<endl;
			summary(diary[index].second);	
		}
		
		else if(command == "show_the_best_day")
		{
			int best_word_count = 0;
			int index = 0;
			
			for(unsigned int i = 0; i< diary.size();i++)
			{
				int entry_pos_words = 0;
				for(auto line : diary[i].second)
					{
						entry_pos_words += countPositiveWords(line,positive_words);
					}
				if(entry_pos_words > best_word_count)
				{
					best_word_count = entry_pos_words;
					index = i;
				}
				
			}
			cout<<diary[index].first<<endl;
			summary(diary[index].second);	
		}
		
		//add line to the last day if no command was given
		else
		{
			for(unsigned int i = 0; i< diary.size();i++)
			{
				if(diary[i].first == date)
				{
					diary[i].second.push_back(inputLine);
					break;
				}
			}			
		}
		
		

	}
	
	


	return 0;
}

int countPositiveWords(string sentence, vector<string> PositiveWords)
{
	stringstream ss(sentence);
	string word;
	int count = 0;
	
	while (ss>> word)
	{
		if(find(PositiveWords.begin(),PositiveWords.end(),word) != PositiveWords.end())
		{
			count++;
		}
	}
	
	return count;
}

void summary(vector<string> entry)
{
	unsigned int length = 20;
	for(auto line : entry)
	{
		if(line.size() < length)
		{
			cout<<line<<endl;
			length -= line.size();
		}
		
		else
		{
			cout<<line.substr(0,length)<<"..."<<endl;
			break;
		}
	}
}
