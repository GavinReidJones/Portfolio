#include <vector>


void CalcPoint(std::vector<std::vector<std::vector<float>>> &Model, double r, int i, int j, int t)
{
	float fNewTemp = (1 - 4 * r)*Model[i][j][t] + r*(Model[i - 1][j][t] + Model[i + 1][j][t] + Model[i][j - 1][t] + Model[i][j + 1][t]);
	Model[i][j].push_back(fNewTemp);
}

void CalcInsulatedBoundary(std::vector<std::vector<std::vector<float>>>& Model, double r, int i, int j, int t, int boundary)
{
	switch (boundary)
	{
	case 0:
		if (j == 0)
		{
			float fNewTemp = (1 - 4 * r)*Model[i][j][t] + r*(2 * Model[i - 1][j][t] + 2 * Model[i][j + 1][t]);
			Model[i][j].push_back(fNewTemp);
		}
		else if (j == Model[i].size() - 1)
		{
			float fNewTemp = (1 - 4 * r)*Model[i][j][t] + r*(2 * Model[i - 1][j][t] + 2 * Model[i][j - 1][t]);
			Model[i][j].push_back(fNewTemp);
		}
		else
		{
			float fNewTemp = (1 - 4 * r)*Model[i][j][t] + r*(2 * Model[i - 1][j][t] + Model[i][j - 1][t] + Model[i][j + 1][t]);
			Model[i][j].push_back(fNewTemp);
		}
		break;
	case 1:
		if (j == 0)
		{
			float fNewTemp = (1 - 4 * r)*Model[i][j][t] + r*(2 * Model[i + 1][j][t] + 2 * Model[i][j + 1][t]);
			Model[i][j].push_back(fNewTemp);
		}
		else if (j == Model[i].size() - 1)
		{
			float fNewTemp = (1 - 4 * r)*Model[i][j][t] + r*(2 * Model[i + 1][j][t] + 2 * Model[i][j - 1][t]);
			Model[i][j].push_back(fNewTemp);
		}
		else
		{
			float fNewTemp = (1 - 4 * r)*Model[i][j][t] + r*(2 * Model[i + 1][j][t] + Model[i][j - 1][t] + Model[i][j + 1][t]);
			Model[i][j].push_back(fNewTemp);
		}
		break;
	case 2:
		if (i == 0)
		{
			float fNewTemp = (1 - 4 * r)*Model[i][j][t] + r*(2 * Model[i + 1][j][t] + 2 * Model[i][j - 1][t]);
			Model[i][j].push_back(fNewTemp);
		}
		else if (i == Model[i].size() - 1)
		{
			float fNewTemp = (1 - 4 * r)*Model[i][j][t] + r*(2 * Model[i - 1][j][t] + 2 * Model[i][j - 1][t]);
			Model[i][j].push_back(fNewTemp);
		}
		else
		{
			float fNewTemp = (1 - 4 * r)*Model[i][j][t] + r*(Model[i + 1][j][t] + Model[i - 1][j][t] + 2 * Model[i][j - 1][t]);
			Model[i][j].push_back(fNewTemp);
		}
		break;
	case 3:

		if (i == 0)
		{
			float fNewTemp = (1 - 4 * r)*Model[i][j][t] + r*(2 * Model[i + 1][j][t] + 2 * Model[i][j + 1][t]);
			Model[i][j].push_back(fNewTemp);
		}
		else if (i == Model[i].size() - 1)
		{
			float fNewTemp = (1 - 4 * r)*Model[i][j][t] + r*(2 * Model[i - 1][j][t] + 2 * Model[i][j + 1][t]);
			Model[i][j].push_back(fNewTemp);
		}
		else
		{
			float fNewTemp = (1 - 4 * r)*Model[i][j][t] + r*(Model[i + 1][j][t] + Model[i - 1][j][t] + 2 * Model[i][j + 1][t]);
			Model[i][j].push_back(fNewTemp);
		}
		break;
	}
}

