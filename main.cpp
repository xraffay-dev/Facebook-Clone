#include<iostream>
#include<fstream>

using namespace std;

class User;
class Facebook;
class Date;
class Activity;
class Object;
class Page;
class Post;
class Comment;
class Memory;

class Helper
{
public:
	static int GetLength(const char* str)
	{
		if (str != nullptr)
		{
			int count = 0;
			while (str[count] != '\0')
			{
				count++;
			}
			return count;
		}
		return 0;
	}
	static void CopyString(char*& dest, char*& src)
	{
		if (dest != nullptr && src != nullptr)
		{
			int i = 0;
			while (src[i] != '\0')
			{
				dest[i] = src[i];
				i++;
			}
			dest[i] = '\0';
		}
	}
	static char* GetStringFromBuffer(char* buffer)
	{
		if (buffer != nullptr)
		{
			int length = GetLength(buffer);
			char* final = new char[length + 1];
			CopyString(final, buffer);
			return final;
		}
		return nullptr;
	}
	static int CompareStrings(const char* str1, const char* str2)
	{
		while (*str1 != '\0' && *str1 == *str2) {
			str1++;
			str2++;
		}
		if (*str1 < *str2) {
			return -1;
		}
		else if (*str1 > *str2) {
			return 1;
		}
		else {
			return 0;
		}
	}
	static char* IntIntoChar(int num)
	{
		int length = 0;
		int temp = num;
		while (num != 0)
		{
			num /= 10;
			length++;
		}
		num = temp;
		char* convertedNum = new char[length + 1];
		int* toBeConvertedNum = new int[length];
		for (int i = 0; i < length; i++)
		{
			toBeConvertedNum[i] = num % 10;
			num /= 10;
		}
		for (int i = length - 1, j = 0; i >= 0; i--, j++)
		{
			convertedNum[i] = toBeConvertedNum[j] + '0';
		}
		convertedNum[length] = '\0';
		return convertedNum;
	}
	static void ConcatenateString(char*& ID)
	{
		char buffer[80];
		buffer[0] = 'c';
		int i;
		int j = 0;
		for (i = 1, j = 0; ID[j] != '\0'; i++, j++)
		{
			buffer[i] = ID[j];
		}
		buffer[i] = '\0';
		ID = Helper::GetStringFromBuffer(buffer);
	}
};
class Date
{
private:
	int date;
	int month;
	int year;
public:
	static Date currentDate;
	Date()
	{
		date = month = year = 0;
	}
	void YearDifference()
	{
		cout << currentDate.year - year;
	}
	void ReadDataFromFile(fstream& myData)
	{
		myData >> date;
		myData >> month;
		myData >> year;
	}
	static void SetCurrentDate(int d, int m, int y)
	{
		currentDate.date = d;
		currentDate.month = m;
		currentDate.year = y;
	}
	static void printDate()
	{
		cout << currentDate.date << "/" << currentDate.month << "/" << currentDate.year << endl;
	}
	bool CompareDate()
	{
		if (date == currentDate.date || date == currentDate.date - 1)
			return true;
		return false;
	}
	bool MemoriesCheck()
	{
		if (currentDate.date == date && currentDate.month == month && currentDate.year > year)
		{
			cout << "On this day " << currentDate.year - year << " years ago" << endl;
			return true;
		}
		return false;
	}
	~Date()
	{
		//Does Nothing
	}
};
class Activity
{
private:
	int Type;
	const char* emotion;
	char* value;
public:
	Activity()
	{
		Type = 0;
		emotion = 0;
		value = 0;
	}
	void ReadDataFromFile(fstream& myData)
	{
		char buffer[80];
		myData >> Type;
		if (Type == 1)
		{
			emotion = { " feeling \0" };
		}
		else if (Type == 2)
		{
			emotion = { " thinking about \0" };
		}
		else if (Type == 3)
		{
			emotion = { " making \0" };
		}
		else if (Type == 4)
		{
			emotion = { " celebrating \0" };
		}
		else
		{
			emotion = { " Invalid \0" };
		}
		myData.getline(buffer, 80);
		value = Helper::GetStringFromBuffer(buffer);
	}
	void PrintActivity(int PostType)
	{
		if (PostType == 1)
		{
			cout << " shared ";
		}
		else
		{
			if (emotion != nullptr)
				cout << " is " << emotion << value << endl;
		}
	}
	~Activity()
	{
		if (value)
			delete[]value;
	}
};
class Object
{
protected:
	char* ID;
public:
	Object()
	{
		ID = 0;
	}
	virtual void AddPostToTimeline(Post*) = 0;
	virtual void printName() = 0;
	virtual void printInformation() = 0;
	virtual void LikePost(Post*) = 0;
	virtual ~Object()
	{
		if (ID)
			delete[]ID;
	}
};
class Comment
{
private:
	char* ID, * text;
	Object* commentBy;
public:
	static int totalComments;
	Comment()
	{
		ID = text = 0;
		commentBy = 0;
	}
	void SetValues(char* ID, char* text, Object* commentBy)
	{
		if (ID)
			this->ID = Helper::GetStringFromBuffer(ID);
		this->text = Helper::GetStringFromBuffer(text);
		this->commentBy = commentBy;
		Comment::totalComments++;
	}
	void printComment()
	{
		commentBy->printName();
		cout << " wrote: \"";
		cout << text;
		cout << "\"" << endl;
	}
	~Comment()
	{
		if (ID)
			delete[]ID;
		if (text)
			delete[]text;
	}
};
class Post
{
private:

	Activity* activity;
	Object** LikedBy;
	int likesCounter;
	Comment** comments;
	int commentsCounter;
	int PostType;
	char* ID;
protected:
	char* Text;
	Date SharedDate;
	Object* SharedBy;
public:
	Post()
	{
		Text = 0;
		ID = 0;
		activity = 0;
		likesCounter = 0;
		commentsCounter = 0;
		comments = 0;
		LikedBy = 0;
		PostType = 0;
		SharedBy = 0;
	}
	Date getDate()
	{
		return SharedDate;
	}
	char* getPostID()
	{
		return ID;
	}
	void ReadDataFromFile(fstream& myData)
	{
		char buffer[80]{ '\0' };
		myData >> PostType;
		myData >> buffer;
		ID = Helper::GetStringFromBuffer(buffer);
		//  SharedDate=Date(day, month, year); Creates a new Date object with the specified d, m, and y values and then assigns to the sharedDate variable.
		SharedDate.ReadDataFromFile(myData);
		myData.ignore(1, '\n');
		myData.getline(buffer, 80);
		Text = Helper::GetStringFromBuffer(buffer);
		if (PostType == 2)
		{
			activity = new Activity();
			activity->ReadDataFromFile(myData);
		}
	}
	void SetSharedBy(Object* sharedBy)
	{
		if (sharedBy != nullptr)
			SharedBy = sharedBy;
	}
	void SetLikedBy(Object* likedBy)
	{
		if (LikedBy == nullptr)
		{
			LikedBy = new Object * [20];
			for (int i = 0; i < 20; i++)
				LikedBy[i] = 0;
		}
		if (likedBy != nullptr)
		{
			LikedBy[likesCounter] = likedBy;
			likesCounter++;
		}
	}
	void AddComment(Comment* commentBy)
	{
		if (comments == nullptr)
		{
			comments = new Comment * [20];
			for (int i = 0; i < 20; i++)
				comments[i] = 0;
		}
		if (commentBy != nullptr)
		{
			comments[commentsCounter] = commentBy;
			commentsCounter++;
		}
	}
	void printLikedBy()
	{
		if (likesCounter > 0)
		{
			cout << "Post Liked By: " << endl;
			for (int i = 0; i < likesCounter; i++)
			{
				if (LikedBy[i] != nullptr)
					LikedBy[i]->printInformation();
			}
		}
		else
			cout << "No one has liked the post yet." << endl;
	}
	virtual void PrintPost()
	{
		cout << "-- ";
		this->SharedBy->printName();
		this->activity->PrintActivity(PostType);
		cout << "\"" << this->Text << "\"" << "\t";
		SharedDate.printDate();
		cout << "Comment Section:-" << endl;
		if (commentsCounter > 0)
		{
			for (int i = 0; i < commentsCounter; i++)
			{
				if (comments[i] != nullptr)
					comments[i]->printComment();
			}
		}
		else
		{
			cout << "No one commented on the post:(" << endl;
		}
	}
	void Timeline()
	{
		bool flag = this->SharedDate.CompareDate();
		if (flag)
		{
			if (this != nullptr)
				this->PrintPost();
		}
	}
	~Post()
	{
		if (Text)
			delete[]Text;
		if (ID)
			delete[]ID;
		if (activity)
			delete activity;
		if (LikedBy)
			delete[]LikedBy;
		for (int i = 0; i < commentsCounter; i++)
		{
			if (comments[i])
				delete comments[i];
		}
		if(comments)
		delete[]comments;
	}
};
class Memory : public Post
{
private:
	Post* originalPost;
public:
	Memory(const char* temp = nullptr)
	{
		char buffer[80];
		int i = 0;
		for (i; temp[i] != '\0'; i++)
			buffer[i] = temp[i];
		buffer[i] = '\0';
		Text = Helper::GetStringFromBuffer(buffer);
		originalPost = 0;
		SharedDate = Date::currentDate;
	}
	void SetOriginalPost(Post* ptr)
	{
		originalPost = ptr;
	}
	void PrintPost()
	{
		cout << "-----";
		SharedBy->printName();
		cout << " shared a memory------\n";
		cout << Text;
		cout << endl;
		(originalPost->getDate()).YearDifference();
		cout << " years ago\n";
		originalPost->PrintPost();

	}
	static void checkMemory(Post* post)
	{
		Date sharedDate = post->getDate();
		if (sharedDate.MemoriesCheck())
		{
			if (post != nullptr)
				post->PrintPost();
		}
	}
	~Memory()
	{
	}
};
class Page : public Object
{
private:
	char* ID;
	char* Title;
	Post** timeline;
	int numPostsInTimeline;
public:
	char* getPageID()
	{
		return ID;
	}
	Page()
	{
		ID = Title = 0;
		numPostsInTimeline = 0;
		timeline = 0;
	}
	void printName()
	{
		cout << Title;
	}
	void ReadDataFromFile(fstream& myData)
	{
		char buffer[80];
		myData >> buffer;
		ID = Helper::GetStringFromBuffer(buffer);
		myData.getline(buffer, 80);
		Title = Helper::GetStringFromBuffer(buffer);
	}
	void AddPostToTimeline(Post* post)
	{
		if (timeline == nullptr)
		{
			timeline = new Post * [1];
			timeline[0] = post;
			numPostsInTimeline++;
		}
		else
		{
			Post** newTimeline = new Post * [numPostsInTimeline + 1];
			for (int i = 0; i < numPostsInTimeline; i++)
			{
				newTimeline[i] = timeline[i];
			}
			newTimeline[numPostsInTimeline] = post;
			numPostsInTimeline++;
			delete[] timeline;
			timeline = newTimeline;
		}
	}
	void printInformation()
	{
		cout << ID << " - " << Title << endl;
	}
	void LikePost(Post* toBeLiked)
	{
		if (toBeLiked != nullptr)
			toBeLiked->SetLikedBy(this);
	}
	void ViewHome()
	{
		for (int i = 0; i < numPostsInTimeline; i++)
		{
			if (timeline[i] != nullptr)
				this->timeline[i]->Timeline();
		}
	}
	void ViewTimeline()
	{
		if (numPostsInTimeline > 0)
		{
			for (int i = 0; i < numPostsInTimeline; i++)
			{
				if (timeline[i] != nullptr)
					timeline[i]->PrintPost();
			}
		}
		else
			cout << "The page has not posted anything yet.";
	}
	~Page()
	{
		if (Title)
		delete[]Title;
		for (int i = 0; i < numPostsInTimeline; i++)
		{
			if (timeline[i])
				delete timeline[i];
		}
		if (timeline)
		{
		   delete[]timeline;
		}
	}
};
class User : public Object
{
private:
	char* ID;
	char* firstName;
	char* lastName;
	int LikedPagesCounter;
	int AddedFriendsCounter;
	Page** LikedPages;
	User** FriendList;
	Post** timeline;
	int numPostsInTimeline;
public:
	char* getUserID()
	{
		return ID;
	}
	User()
	{
		ID = firstName = lastName = 0;
		LikedPages = nullptr;
		FriendList = nullptr;
		timeline = 0;
		LikedPagesCounter = 0;
		AddedFriendsCounter = 0;
		numPostsInTimeline = 0;
	}
	void ReadDataFromFile(fstream& myData)
	{
		char buffer[80];
		myData >> buffer;
		ID = Helper::GetStringFromBuffer(buffer);
		myData >> buffer;
		firstName = Helper::GetStringFromBuffer(buffer);
		myData >> buffer;
		lastName = Helper::GetStringFromBuffer(buffer);
		*buffer = {};
	}
	void ReadLikedPagesFromFile(Page** array, int size)
	{
		if (LikedPages == nullptr)
		{
			LikedPages = new Page * [12];
			for (int i = 0; i < 12; i++)
				LikedPages[i] = 0;
		}
		if (array != nullptr)
		{
			LikedPagesCounter = size;
			for (int i = 0; i < size; i++)
			{
				LikedPages[i] = array[i];
			}
		}
	}
	void AssociateFriend(User* Friend)
	{
		if (FriendList == nullptr)
		{
			FriendList = new User * [20];
			for (int i = 0; i < 20; i++)
				FriendList[i] = 0;
		}
		if (Friend != nullptr)
		{
			if (Friend != nullptr)
			{
				FriendList[AddedFriendsCounter] = Friend;
				AddedFriendsCounter++;
			}
		}
	}
	void printName()
	{
		cout << firstName << " " << lastName;
	}
	void printInformation()
	{
		cout << ID << " - " << firstName << " " << lastName << endl;
	}
	void LikePost(Post* toBeLiked)
	{
		if (toBeLiked != nullptr)
			toBeLiked->SetLikedBy(this);
	}
	void printFriendList()
	{
		if (AddedFriendsCounter > 0)
		{
			for (int i = 0; i < AddedFriendsCounter; i++)
			{
				if (FriendList[i] != nullptr)
					FriendList[i]->printInformation();
			}
		}
		else
			cout << "The user has no friends." << endl;
	}
	void printLikedPagesList()
	{
		if (LikedPagesCounter > 0)
		{
			for (int i = 0; i < LikedPagesCounter; i++)
			{
				if (LikedPages[i] != nullptr)
					LikedPages[i]->printInformation();
			}
		}
		else
			cout << "The user has not liked any pages." << endl;
	}
	void AddPostToTimeline(Post* post)
	{
		if (timeline == nullptr)
		{
			timeline = new Post * [1];
			timeline[0] = post;
			numPostsInTimeline++;
		}
		else {
			Post** newTimeline = new Post * [numPostsInTimeline + 1];
			for (int i = 0; i < numPostsInTimeline; i++)
			{
				newTimeline[i] = timeline[i];
			}
			newTimeline[numPostsInTimeline] = post;
			numPostsInTimeline++;
			delete[] timeline;
			timeline = newTimeline;
		}
	}
	void ViewHome()
	{
		for (int i = 0; i < AddedFriendsCounter; i++)
		{
			for (int j = 0; j < FriendList[i]->numPostsInTimeline; j++)
			{
				if (FriendList[i]->timeline[j] != nullptr)
					FriendList[i]->timeline[j]->Timeline();
			}
		}
		for (int i = 0; i < LikedPagesCounter; i++)
		{
			if (LikedPages[i] != nullptr)
				LikedPages[i]->ViewHome();
		}
	}
	void ViewTimeline()
	{
		if (numPostsInTimeline > 0)
		{
			for (int i = 0; i < numPostsInTimeline; i++)
			{
				if (timeline[i] != nullptr)
					timeline[i]->Timeline();
			}
		}
		else
			cout << "The user has not posted anything yet.";
	}
	void Memories()
	{
		cout << "\"We hope you enjoy looking back and sharing your memories on Facebook, from the most recent to those long ago.\"" << endl;
		for (int i = 0; i < numPostsInTimeline; i++)
		{
			if (timeline[i] != nullptr)
				Memory::checkMemory(timeline[i]);
		}
	}
	~User()
	{
		if (firstName)
			delete[]firstName;
		if (lastName)
			delete[]lastName;
		if (LikedPages)
			delete[]LikedPages;
		if (FriendList)
			delete[]FriendList;
		for (int i = 0; i < numPostsInTimeline; i++)
		{
			if (timeline[i])
				delete timeline[i];
		}
		if (timeline)
		{
			delete[]timeline;
		}
	}
};
class FaceBook
{
private:
	Page** pages;
	User** users;
	Post** posts;
	Comment** comments;
public:
	FaceBook()
	{
		pages = nullptr;
		users = nullptr;
		posts = nullptr;
		comments = nullptr;
	}
	User* searchUserByID(const char* buffer)
	{
		char* currentUserID;
		int j;
		for (int i = 0; i < 20; i++)
		{
			bool flag = true;
			currentUserID = users[i]->getUserID();
			int length1 = Helper::GetLength(currentUserID);
			int length2 = Helper::GetLength(buffer);
			for (j = 0; j < length1; j++)
			{
				if (currentUserID[j] != buffer[j] || length1 != length2)
				{
					flag = false;
					break;
				}
			}
			if (flag)
			{
				return users[i];
			}
		}
		return nullptr;
	}
	User* searchTempUsers(char*& buffer)
	{
		char* currentUserID;
		int count = 0;
		int j;
		for (int i = 0; i < 20; i++)
		{
			bool flag = true;
			currentUserID = users[i]->getUserID();
			int length1 = Helper::GetLength(currentUserID);
			int length2 = Helper::GetLength(buffer);
			for (j = 0; j < length1; j++)
			{
				if (currentUserID[j] != buffer[j] || length1 != length2)
				{
					flag = false;
					break;
				}
			}
			if (flag)
			{
				return users[i];
			}
		}
		return nullptr;
	}
	Page* SearchPageByID(const char* buffer)
	{
		char* currentPageID;
		for (int i = 0; i < 12; i++)
		{
			bool flag = true;
			currentPageID = pages[i]->getPageID();
			int length1 = Helper::GetLength(currentPageID);
			int length2 = Helper::GetLength(buffer);
			for (int j = 0; j < length1; j++)
			{
				if (currentPageID[j] != buffer[j] || length1 != length2)
				{
					flag = false;
					break;
				}
			}
			if (flag)
			{
				return pages[i];
			}
		}
		return nullptr;
	}
	Post* searchPostByID(const char* buffer)
	{
		char* currentPostID;
		int j;
		for (int i = 0; i < 11; i++)
		{
			bool flag = true;
			currentPostID = posts[i]->getPostID();
			int length1 = Helper::GetLength(buffer);
			int length2 = Helper::GetLength(currentPostID);
			for (j = 0; currentPostID[j] != '\0'; j++)
			{
				if (currentPostID[j] != buffer[j] || length1 != length2)
				{
					flag = false;
					break;
				}
			}
			if (flag)
			{
				return posts[i];
			}
		}
		return nullptr;
	}
	Object* searchObjectByID(const char* ID)
	{
		if (ID[0] == 'u')
			return searchUserByID(ID);
		else
			return SearchPageByID(ID);
	}
	void LoadPagesFromFile(const char* myFile)
	{
		fstream myData;
		myData.open(myFile, ios::in);
		if (myData)
		{
			int total;
			myData >> total;
			pages = new Page * [total];
			for (int i = 0; i < total; i++)
			{
				pages[i] = new Page;
				pages[i]->ReadDataFromFile(myData);
			}
		}
		else
		{
			cout << "NO PAGES INFORMATION EXISTS";
		}
		myData.close();
	}
	void LoadUsersFromFile(const char* myFile)
	{
		fstream myData;
		char*** temp = nullptr;
		Page** tempLikedPages = nullptr;
		User** tempAddedFriends = nullptr;
		char buffer[80];
		myData.open(myFile, ios::in);
		if (myData)
		{
			int k = 0;
			int total;
			myData >> total;
			users = new User * [total];
			temp = new char** [total];
			tempLikedPages = new Page * [12];
			tempAddedFriends = new User * [20];
			for (int i = 0; i < total; i++)
			{
				temp[i] = new char* [10];
			}
			for (int i = 0; i < total; i++)
			{
				users[i] = new User;
				users[i]->ReadDataFromFile(myData);
				int j = 0;
				while (true)
				{
					myData >> buffer;
					if (Helper::CompareStrings(buffer, "-1") == 0)
					{
						temp[i][j] = nullptr;
						break;
					}
					temp[i][j] = Helper::GetStringFromBuffer(buffer);
					temp[i][j + 1] = nullptr;
					j++;
				}
				while (1)
				{
					myData >> buffer;
					if (*buffer == '-')
					{
						break;
					}
					else
					{
						tempLikedPages[k] = SearchPageByID(buffer);
						k++;
					}
				}
				users[i]->ReadLikedPagesFromFile(tempLikedPages, k);
				k = 0;
			}
			//	Association of user with friends
			for (int i = 0; i < total; i++)
			{
				for (int j = 0; temp[i][j] != nullptr; j++)
				{
					users[i]->AssociateFriend(searchTempUsers(temp[i][j]));
				}
			}
			//DEALLOCATION OF MEMORY
			for (int i = 0; i < total; i++)
			{
				delete temp[i];
			}
			delete[] temp;
			delete[]tempLikedPages;
			delete[]tempAddedFriends;
			temp = nullptr;
			temp = nullptr;
			tempAddedFriends = nullptr;
		}
		else
		{
			cout << "\nNO USERS INFORMATION EXISTS";
		}
		myData.close();
	}
	void LoadPostsFromFile(const char* myFile)
	{
		fstream myData;
		myData.open(myFile, ios::in);
		if (myData)
		{
			int total;
			//int postType;
			myData >> total;
			posts = new Post * [total];
			char UiOrPi[80];
			char buffer[80]{ '\0' };
			for (int i = 0; i < total; i++)
			{
				posts[i] = new Post;
				posts[i]->ReadDataFromFile(myData);
				myData >> UiOrPi;
				Object* sharedBy = searchObjectByID(UiOrPi);
				posts[i]->SetSharedBy(sharedBy);
				sharedBy->AddPostToTimeline(posts[i]);
				int j = 0;
				while (1)
				{
					myData >> buffer;
					if (*buffer == '-')
						break;
					else
					{
						Object* LikedBy = searchObjectByID(buffer);
						posts[i]->SetLikedBy(LikedBy);
					}
				}
			}
			myData.close();
		}
		else
		{
			cout << "NO POSTS DATA EXIST." << endl;
		}
	}
	void LoadCommentsFromFile(const char* myFile)
	{
		fstream myData;
		myData.open(myFile, ios::in);
		int total;
		if (myData)
		{
			myData >> total;
			comments = new Comment * [total];
			char ID[80], postID[80], text[80], commentBy[80];
			for (int i = 0; i < total; i++)
			{
				Comment* comment = new Comment;
				myData >> ID;
				myData >> postID;
				Post* postPtr = searchPostByID(postID);
				postPtr->AddComment(comment);
				myData >> commentBy;
				Object* UiOrPi = searchObjectByID(commentBy);
				myData.getline(text, 80);
				comment->SetValues(ID, text, UiOrPi);
			}
			myData.close();
		}
		else
		{
			cout << "NO COMMENTS DATA EXIST." << endl;
		}
	}
	void Load()
	{
		LoadPagesFromFile("SocialMediaPages.txt");
		LoadUsersFromFile("SocialMediaUsers.txt");
		LoadPostsFromFile("SocialNetworkPosts.txt");
		LoadCommentsFromFile("SocialNetworkComments.txt");
	}
	static void SocialMediaCommander()
	{
		char* ID;
		FaceBook fb;
		cout << "-------------------------------------------------------------------------------------------------" << endl;
		cout << "Command:\tSet current System Date 14 11 2017" << endl;
		Date::SetCurrentDate(15, 11, 2017);
		cout << "System Date:\t";
		Date::printDate();
		cout << "-------------------------------------------------------------------------------------------------" << endl;
		fb.Load();
		cout << "Command:\tSet current User to U7 " << endl;
		User* currentUser = fb.searchUserByID("u7");
		currentUser->printName();
		cout << " successfully set as current user." << endl;
		cout << "-------------------------------------------------------------------------------------------------" << endl;
		cout << "Command:\tView Friends List " << endl;
		cout << "-------------------------------------------------------------------------------------------------" << endl;
		currentUser->printName();
		cout << " - Friend List" << endl;
		currentUser->printFriendList();
		cout << "-------------------------------------------------------------------------------------------------" << endl;
		cout << "Command:\tView Liked List" << endl;
		cout << "-------------------------------------------------------------------------------------------------" << endl;
		currentUser->printName();
		cout << " - Liked Pages List" << endl;
		currentUser->printLikedPagesList();
		cout << "-------------------------------------------------------------------------------------------------" << endl;
		cout << "Command:\tView Home Page" << endl;
		cout << "-------------------------------------------------------------------------------------------------" << endl;
		currentUser->printName();
		cout << " - Home Page" << endl;
		currentUser->ViewHome();
		cout << "-------------------------------------------------------------------------------------------------" << endl;
		cout << "Command:\tView Timeline" << endl;
		cout << "-------------------------------------------------------------------------------------------------" << endl;
		currentUser->printName();
		cout << " - Timeline" << endl;
		currentUser->ViewTimeline();
		cout << "-------------------------------------------------------------------------------------------------" << endl;
		cout << "Command:\tView Liked List" << endl;
		cout << "-------------------------------------------------------------------------------------------------" << endl;
		Post* currentPost = fb.searchPostByID("post5");
		currentPost->printLikedBy();
		cout << "-------------------------------------------------------------------------------------------------" << endl;
		cout << "Command:\tLike Post" << endl;
		cout << "-------------------------------------------------------------------------------------------------" << endl;
		currentUser->LikePost(currentPost);
		cout << "Command:\tView Liked List" << endl;
		currentPost->printLikedBy();
		cout << "-------------------------------------------------------------------------------------------------" << endl;
		cout << "Command:\tPost Comment: \"Good Luck for your Result\"" << endl;
		Comment* commentToBeDone = new Comment;
		currentPost = fb.searchPostByID("post4");
		currentPost->AddComment(commentToBeDone);
		char comment1[] = { "Good Luck for your Result" };
		ID = Helper::IntIntoChar(Comment::totalComments);
		Helper::ConcatenateString(ID);
		commentToBeDone->SetValues(ID, comment1, currentUser);
		cout << "Command:\tView Post" << endl;
		currentPost->PrintPost();
		cout << "-------------------------------------------------------------------------------------------------" << endl;
		cout << "Command:\tPost Comment: \"Thanks for the wishes\"" << endl;
		Comment* commentToBeDone2 = new Comment;
		currentPost = fb.searchPostByID("post8");
		currentPost->AddComment(commentToBeDone2);
		char comment2[] = { "Thanks for the wishes" };
		ID = Helper::IntIntoChar(Comment::totalComments);
		Helper::ConcatenateString(ID);
		commentToBeDone2->SetValues(ID, comment2, currentUser);
		cout << "Command:\tView Post" << endl;
		currentPost->PrintPost();
		cout << "-------------------------------------------------------------------------------------------------" << endl;
		cout << "Command:\tSee Your Memories" << endl;
		currentUser->Memories();
		cout << "-------------------------------------------------------------------------------------------------" << endl;
		const char* memoryText;
		memoryText = {"Never thought I will be specialist in this field..."};
		cout << "Command:\tShare Memory: \"Never thought I will be specialist in this field...\"" << endl;
		Memory* memo = new Memory(memoryText);
		currentPost = fb.searchPostByID("post10");
		memo->SetOriginalPost(currentPost);
		memo->SetSharedBy(currentUser);
		currentUser->AddPostToTimeline(memo);
		currentUser->ViewTimeline();
		cout << "-------------------------------------------------------------------------------------------------" << endl;
		cout << "Command:\tView Page" << endl;
		Page* currentPage = fb.SearchPageByID("p1");
		currentPage->ViewTimeline();
		cout << "-------------------------------------------------------------------------------------------------" << endl;
		cout << "Command:\tSet current user \"u11\"" << endl;
		currentUser = fb.searchUserByID("u11");
		cout << "-------------------------------------------------------------------------------------------------" << endl;
		currentUser->printName();
		cout << " successfully set as current user." << endl;
		cout << "Command:\tView Home" << endl;
		currentUser->ViewHome();
		cout << "-------------------------------------------------------------------------------------------------" << endl;
		cout << "Command:\tView Timeline" << endl;
		currentUser->ViewTimeline();
		cout << "-------------------------------------------------------------------------------------------------" << endl;
	}
	~FaceBook()
	{
		for (int i = 0; i < 20; i++)
		{
			if (users[i])
				delete users[i];
		}
		if (users)
		{
			delete[]users;
		}
		for (int i = 0; i < 12; i++)
		{
			if (pages[i])
				delete pages[i];
		}
		if (pages)
		{
			delete[]pages;
		}
		if (posts)
			delete[]posts;
		if (comments)
			delete[]comments;
	}
};

Date Date::currentDate;
int Comment::totalComments = 0;

int main()
{
	FaceBook::SocialMediaCommander();
	return 0;
}
