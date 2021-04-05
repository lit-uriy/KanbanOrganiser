#ifndef POSTPONEDCARD_H
#define POSTPONEDCARD_H



class PostponedCard
{
	public:
		PostponedCard(unsigned long long id, int minutes=0);

		unsigned long long Id;
		int Minutes;

		bool operator==( const PostponedCard& other);
};


#endif // POSTPONEDCARD_H
