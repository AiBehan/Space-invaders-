#pragma once

struct ScreenBuffer
{
public:
	// Default Constructor.
	ScreenBuffer() : row(0), col(0), m_buffer(nullptr) {}
	// Parameterised Constructor.
	ScreenBuffer(int x, int y) : row(x), col(y)
	{
		// Allocate our buffer.
		m_buffer = new char* [row];
		for (int i = 0; i < row; ++i)
		{
			m_buffer[i] = new char[col];
		}
	};
	// Copy Constructor.
	ScreenBuffer(const ScreenBuffer& other) : row(other.row), col(other.col)
	{
		// Allocate Memory.
		m_buffer = new char* [row];
		for (int i = 0; i < row; ++i)
		{
			m_buffer[i] = new char[col];
		}

		// Copy Data.
		for (int i = 0; i < row; ++i)
		{
			for (int j = 0; j < col; ++j)
			{
				m_buffer[i][j] = other.m_buffer[i][j];
			}
		}
	}
	// Move Constructor.
	ScreenBuffer(ScreenBuffer&& other) noexcept
		: row(other.row), col(other.col), m_buffer(other.m_buffer)
	{
		// Reset the source object.
		other.row = 0;
		other.col = 0;
		other.m_buffer = nullptr;
	}
	~ScreenBuffer()
	{
		// Deallocate our buffer.
		for (int i = 0; i < row; ++i)
		{
			// If we don't deallocate each sub-array of our buffer before deallocating the
			// buffer itself, those arrays will remain allocated and we'll have a memory leak.
			delete[] m_buffer[i];
		}
		delete[] m_buffer;
	};


	// The Copy Assignment Operator.
	// This will be covered more next week (Lecture 9 ("")), but in
	//   essence this copies the data from one ScreenBuffer instance to
	//   another and ensures that there are no shared references.
	// If we do not have this, then when initialising our ScreenBuffer in GameSource::CreateBuffer,
	//   we would inadvertantly deallocate our 'm_buffer'
	ScreenBuffer& operator=(const ScreenBuffer& other)
	{
		if (this == &other)
		{
			return *this;
		}

		// Deallocate existing memory.
		for (int i = 0; i < row; ++i)
		{
			delete[] m_buffer[i];
		}
		delete[] m_buffer;

		// Allocate memory for new data.
		row = other.row;
		col = other.col;
		m_buffer = new char* [row];
		for (int i = 0; i < row; ++i)
		{
			m_buffer[i] = new char[col];
		}

		// Copy the data from 'other' to this object.
		// Along with creating a new array for m_buffer, this prevents us from
		//   inadvertantly sharing our pointers betwee the old and new objects.
		for (int i = 0; i < row; ++i)
		{
			for (int j = 0; j < col; ++j)
			{
				m_buffer[i][j] = other.m_buffer[i][j];
			}
		}
		return *this;
	}
	// Move Assignment Operator.
	// This lets us transfer ownership of the data within one ScreenBuffer instance and another.
	ScreenBuffer& operator=(ScreenBuffer&& other) noexcept
	{
		if (this == &other)
			return *this;

		// Deallocate existing memory.
		for (int i = 0; i < row; ++i)
		{
			delete[] m_buffer[i];
		}
		delete[] m_buffer;

		// Transfer ownership.
		row = other.row;
		col = other.col;
		m_buffer = other.m_buffer;

		// Reset the source object.
		other.row = 0;
		other.col = 0;
		other.m_buffer = nullptr;
	}


	char& getChar(int row, int col)
	{
		return m_buffer[row][col];
	}
	void setChar(int row, int col, char value)
	{
		m_buffer[row][col] = value;
	}


private:
	int row;
	int col;
	char** m_buffer;
};