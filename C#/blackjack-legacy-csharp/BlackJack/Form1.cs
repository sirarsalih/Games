using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;
using System.Collections;
using System.Media;

namespace BlackJack
{
	public partial class Form1 : Form
	{
		Hashtable h1;

		Hashtable h2;

		ArrayList arrayList;

		SoundPlayer soundplayer;

		int sumPlayer;
		int sumDealer;

		bool gameEnded = false;

		bool dealt = false;

		bool newGame = false;

		bool firstHit = false;
		bool secondHit = false;
		bool thirdHit = false;
		bool fourthHit = false;

		Random RandNumber;

		int MyRandomNumber;

		public Form1()
		{
			InitializeComponent();

			soundplayer = new SoundPlayer();

			arrayList = new ArrayList();

			RandNumber = new Random();
			MyRandomNumber = RandNumber.Next(52);


			h1 = new Hashtable(52);
			h1.Add(0, "1_hearts.gif");
			h1.Add(1, "1_spades.gif");
			h1.Add(2, "1_clover.gif");
			h1.Add(3, "1_diamonds.gif");
			h1.Add(4, "2_hearts.gif");
			h1.Add(5, "2_spades.gif");
			h1.Add(6, "2_clover.gif");
			h1.Add(7, "2_diamonds.gif");
			h1.Add(8, "3_hearts.gif");
			h1.Add(9, "3_spades.gif");
			h1.Add(10, "3_clover.gif");
			h1.Add(11, "3_diamonds.gif");
			h1.Add(12, "4_hearts.gif");
			h1.Add(13, "4_spades.gif");
			h1.Add(14, "4_clover.gif");
			h1.Add(15, "4_diamonds.gif");
			h1.Add(16, "5_hearts.gif");
			h1.Add(17, "5_spades.gif");
			h1.Add(18, "5_clover.gif");
			h1.Add(19, "5_diamonds.gif");
			h1.Add(20, "6_hearts.gif");
			h1.Add(21, "6_spades.gif");
			h1.Add(22, "6_clover.gif");
			h1.Add(23, "6_diamonds.gif");
			h1.Add(24, "7_hearts.gif");
			h1.Add(25, "7_spades.gif");
			h1.Add(26, "7_clover.gif");
			h1.Add(27, "7_diamonds.gif");
			h1.Add(28, "8_hearts.gif");
			h1.Add(29, "8_spades.gif");
			h1.Add(30, "8_clover.gif");
			h1.Add(31, "8_diamonds.gif");
			h1.Add(32, "9_hearts.gif");
			h1.Add(33, "9_spades.gif");
			h1.Add(34, "9_clover.gif");
			h1.Add(35, "9_diamonds.gif");
			h1.Add(36, "10_hearts.gif");
			h1.Add(37, "10_spades.gif");
			h1.Add(38, "10_clover.gif");
			h1.Add(39, "10_diamonds.gif");
			h1.Add(40, "11_hearts.gif");
			h1.Add(41, "11_spades.gif");
			h1.Add(42, "11_clover.gif");
			h1.Add(43, "11_diamonds.gif");
			h1.Add(44, "12_hearts.gif");
			h1.Add(45, "12_spades.gif");
			h1.Add(46, "12_clover.gif");
			h1.Add(47, "12_diamonds.gif");
			h1.Add(48, "13_hearts.gif");
			h1.Add(49, "13_spades.gif");
			h1.Add(50, "13_clover.gif");
			h1.Add(51, "13_diamonds.gif");

			h2 = new Hashtable(52);
			h2.Add("1_hearts.gif",11);
			h2.Add("1_spades.gif",11);
			h2.Add("1_clover.gif",11);
			h2.Add("1_diamonds.gif",11);
			h2.Add("2_hearts.gif",2);
			h2.Add("2_spades.gif",2);
			h2.Add("2_clover.gif",2);
			h2.Add("2_diamonds.gif",2);
			h2.Add("3_hearts.gif",3);
			h2.Add("3_spades.gif",3);
			h2.Add("3_clover.gif",3);
			h2.Add("3_diamonds.gif",3);
			h2.Add("4_hearts.gif",4);
			h2.Add("4_spades.gif",4);
			h2.Add("4_clover.gif",4);
			h2.Add("4_diamonds.gif",4);
			h2.Add("5_hearts.gif",5);
			h2.Add("5_spades.gif",5);
			h2.Add("5_clover.gif",5);
			h2.Add("5_diamonds.gif",5);
			h2.Add("6_hearts.gif",6);
			h2.Add("6_spades.gif",6);
			h2.Add("6_clover.gif",6);
			h2.Add("6_diamonds.gif",6);
			h2.Add("7_hearts.gif",7);
			h2.Add("7_spades.gif",7);
			h2.Add("7_clover.gif",7);
			h2.Add("7_diamonds.gif",7);
			h2.Add("8_hearts.gif",8);
			h2.Add("8_spades.gif",8);
			h2.Add("8_clover.gif",8);
			h2.Add("8_diamonds.gif",8);
			h2.Add("9_hearts.gif",9);
			h2.Add("9_spades.gif",9);
			h2.Add("9_clover.gif",9);
			h2.Add("9_diamonds.gif",9);
			h2.Add("10_hearts.gif",10);
			h2.Add("10_spades.gif",10);
			h2.Add("10_clover.gif",10);
			h2.Add("10_diamonds.gif",10);
			h2.Add("11_hearts.gif",10);
			h2.Add("11_spades.gif",10);
			h2.Add("11_clover.gif",10);
			h2.Add("11_diamonds.gif",10);
			h2.Add("12_hearts.gif",10);
			h2.Add("12_spades.gif",10);
			h2.Add("12_clover.gif",10);
			h2.Add("12_diamonds.gif",10);
			h2.Add("13_hearts.gif",10);
			h2.Add("13_spades.gif",10);
			h2.Add("13_clover.gif",10);
			h2.Add("13_diamonds.gif",10);

		}

		private void Form1_Load(object sender, EventArgs e)
		{

			Bitmap dealingCard = new Bitmap(".\\Images\\cover.gif");

			pictureBox12.Image = dealingCard;
			pictureBox13.Image = dealingCard;
			pictureBox14.Image = dealingCard;
			pictureBox15.Image = dealingCard;
			pictureBox16.Image = dealingCard;
			pictureBox17.Image = dealingCard;

		}

		private void pictureBox1_Click(object sender, EventArgs e)
		{
			
		}

		private void pictureBox2_Click(object sender, EventArgs e)
		{

		}

		public int GetCard(PictureBox pictureBox,TextBox textBox, int sum)
		
		{
			try
			{
				if (!arrayList.Contains(MyRandomNumber))
				{
					arrayList.Add(MyRandomNumber);
				}

				else
				{
					MyRandomNumber = RandNumber.Next(52);

					arrayList.Add(MyRandomNumber);
				}

				if (h1.ContainsKey(MyRandomNumber))
				{

					string pictureLink = h1[MyRandomNumber].ToString();
					Bitmap cards = new Bitmap(".\\Images\\" + pictureLink);

					pictureBox.Image = cards;

					int partialsum = (int)h2[pictureLink];

					sum += partialsum;

					textBox.Text = sum.ToString();

				}

			}
			catch (Exception e2)
			{
				MessageBox.Show(e2.ToString());

			}

			return sum;
		}

		private void Hit(object sender, EventArgs e)
		{

			if (dealt)
			{
				if (gameEnded)
				{

					MessageBox.Show("Game is ended. You must start a new game.");

					return;

				}

				soundplayer.SoundLocation = ".\\Sounds\\deal.wav";

				soundplayer.Play();

				pictureBox11.Visible = false;

				if (fourthHit)
				{
					if (sumDealer < 17)
					{
						pictureBox10.Visible = true;
						sumDealer = GetCard(pictureBox10, textBox2, sumDealer);
					}

					if (sumPlayer > 21 && sumDealer > 21)
					{
						MessageBox.Show("You and dealer lose!");

						gameEnded = true;
						newGame = true;

						return;
					}

					if (sumPlayer > 21)
					{

						MessageBox.Show("You lose! Dealer wins!");

						gameEnded = true;
						newGame = true;

						return;

					}

					if (sumDealer > 21)
					{
						MessageBox.Show("Dealer loses! You win!");

						gameEnded = true;
						newGame = true;

						return;
					}

					thirdHit = false;
					fourthHit = true;
				}

				if (thirdHit)
				{
					pictureBox8.Visible = true;
					sumPlayer = GetCard(pictureBox8, textBox1, sumPlayer);

					if (sumDealer < 17)
					{
						pictureBox10.Visible = true;
						sumDealer = GetCard(pictureBox10, textBox2, sumDealer);
					}

					if (sumPlayer > 21 && sumDealer > 21)
					{
						MessageBox.Show("You and dealer lose!");

						gameEnded = true;
						newGame = true;

						return;
					}

					if (sumPlayer > 21)
					{

						MessageBox.Show("You lose! Dealer wins!");

						gameEnded = true;
						newGame = true;

						return;

					}

					if (sumDealer > 21)
					{
						MessageBox.Show("Dealer loses! You win!");

						gameEnded = true;
						newGame = true;

						return;
					}

					thirdHit = false;
					fourthHit = true;
				}

				if (secondHit)
				{
					if (sumDealer >= 11)
					{
						h2["1_hearts.gif"] = 1;
						h2["1_spades.gif"] = 1;
						h2["1_clover.gif"] = 1;
						h2["1_diamonds.gif"] = 1;
					}

					pictureBox7.Visible = true;
					sumPlayer = GetCard(pictureBox7, textBox1, sumPlayer);

					if (sumDealer < 17)
					{
						pictureBox9.Visible = true;
						sumDealer = GetCard(pictureBox9, textBox2, sumDealer);
					}

					if (sumPlayer > 21 && sumDealer > 21)
					{
						MessageBox.Show("You and dealer lose!");

						gameEnded = true;
						newGame = true;

						return;
					}

					if (sumPlayer > 21)
					{

						MessageBox.Show("You lose! Dealer wins!");

						gameEnded = true;
						newGame = true;

						return;

					}

					if (sumDealer > 21)
					{
						MessageBox.Show("Dealer loses! You win!");

						gameEnded = true;
						newGame = true;

						return;
					}

					secondHit = false;
					thirdHit = true;
				}

				if (firstHit)
				{

					if (sumPlayer >= 11)
					{
						h2["1_hearts.gif"] = 1;
						h2["1_spades.gif"] = 1;
						h2["1_clover.gif"] = 1;
						h2["1_diamonds.gif"] = 1;

					}

						pictureBox4.Visible = true;
						sumPlayer = GetCard(pictureBox4, textBox1, sumPlayer);

						pictureBox5.Visible = true;
						sumDealer = GetCard(pictureBox5, textBox2, sumDealer);

						if (sumDealer == 21)
						{
							MessageBox.Show("Blackjack dealer! You lose!");

							gameEnded = true;
							newGame = true;

							return;

						}

						if (sumDealer == 22)
						{

							h2["1_hearts.gif"] = 1;
							h2["1_spades.gif"] = 1;
							h2["1_clover.gif"] = 1;
							h2["1_diamonds.gif"] = 1;

							sumDealer = GetCard(pictureBox5, textBox2, sumDealer);

							h2["1_hearts.gif"] = 11;
							h2["1_spades.gif"] = 11;
							h2["1_clover.gif"] = 11;
							h2["1_diamonds.gif"] = 11;

						}

						if (sumDealer < 17)
						{
							pictureBox6.Visible = true;
							sumDealer = GetCard(pictureBox6, textBox2, sumDealer);
						}

						if (sumPlayer > 21 && sumDealer > 21)
						{
							MessageBox.Show("You and dealer lose!");

							gameEnded = true;
							newGame = true;

							return;
						}

						if (sumDealer > 21)
						{
							MessageBox.Show("Dealer loses! You win!");

							gameEnded = true;
							newGame = true;

							return;
						}

						if (sumPlayer > 21)
						{

							MessageBox.Show("You lose! Dealer wins!");

							gameEnded = true;
							newGame = true;

							return;

						}					

						firstHit = false;
						secondHit = true;

					}
			}
			
			else
			{
				MessageBox.Show("You must be dealt cards first!");
			}
					
		}

		private void Deal(object sender, EventArgs e)
		{

			if (gameEnded)
			{
				MessageBox.Show("Game is ended. You must start a new game.");

				dealt = false;

				return;
			}

			if (dealt)
			{
				MessageBox.Show("Already dealt. Game in progress.");

				return;
			}

			soundplayer.SoundLocation = ".\\Sounds\\deal.wav";

			soundplayer.Play();

			pictureBox4.Visible = false;
			pictureBox5.Visible = false;
			pictureBox6.Visible = false;
			pictureBox7.Visible = false;
			pictureBox8.Visible = false;
			pictureBox9.Visible = false;
			pictureBox10.Visible = false;

			Bitmap coverCard = new Bitmap(".\\Images\\cover.gif");

			pictureBox11.Image = coverCard;

			pictureBox11.Visible = true;

			sumPlayer = GetCard(pictureBox1, textBox1, sumPlayer);
			sumPlayer = GetCard(pictureBox2, textBox1, sumPlayer);

			sumDealer = GetCard(pictureBox3, textBox2, sumDealer);

			if (sumPlayer == 21)
			{
				MessageBox.Show("Blackjack! You win!");

				dealt = true;
				gameEnded = true;
				newGame = true;

				return;			
			}

			if (sumPlayer == 22)
			{

				h2["1_hearts.gif"]   = 1;
				h2["1_spades.gif"]   = 1;
				h2["1_clover.gif"]   = 1;
				h2["1_diamonds.gif"] = 1;

				sumPlayer = GetCard(pictureBox2, textBox1, sumPlayer);

				h2["1_hearts.gif"]   = 11;
				h2["1_spades.gif"]   = 11;
				h2["1_clover.gif"]   = 11;
				h2["1_diamonds.gif"] = 11;				
			
			}

			if (sumDealer == 1)
			{
				h2["1_hearts.gif"]   = 11;
				h2["1_spades.gif"]   = 11;
				h2["1_clover.gif"]   = 11;
				h2["1_diamonds.gif"] = 11;
			
			}

			dealt = true;
			firstHit = true;
			newGame = true;

		}

		private void Stand(object sender, EventArgs e)
		{
			if (dealt)
			{

				if (gameEnded)
				{

					MessageBox.Show("Game is ended. You must start a new game.");

					return;

				}

				if (sumDealer < 17)
				{

					if (!pictureBox5.Visible==true)
					{
						pictureBox11.Visible = false;

						pictureBox5.Visible = true;
						sumDealer = GetCard(pictureBox5, textBox2, sumDealer);
					
					}

					if (sumDealer < 17)
					{
						if (!pictureBox6.Visible == true)
						{
							pictureBox6.Visible = true;
							sumDealer = GetCard(pictureBox6, textBox2, sumDealer);

						}
					
					}

					if (sumDealer < 17)
					{
						if (!pictureBox9.Visible == true)
						{

							pictureBox9.Visible = true;
							sumDealer = GetCard(pictureBox9, textBox2, sumDealer);

						}
					}

					if (sumDealer < 17)
					{
						if (!pictureBox10.Visible == true)
						{

							pictureBox10.Visible = true;
							sumDealer = GetCard(pictureBox10, textBox2, sumDealer);

						}
					}				
				}

				if (sumDealer > sumPlayer && sumDealer <= 21)
				{
					MessageBox.Show("Dealer wins! You lose!");

					gameEnded = true;
					newGame = true;

				}

				if (sumPlayer > sumDealer && sumPlayer <= 21)
				{
					MessageBox.Show("You win! Dealer loses!");

					gameEnded = true;
					newGame = true;

				}

				if (sumPlayer == sumDealer)
				{
					MessageBox.Show("Push!");

					gameEnded = true;
					newGame = true;
				}

				if (sumDealer > 21)
				{
					MessageBox.Show("Dealer loses! You win!");

					gameEnded = true;
					newGame = true;
				}

				if (sumPlayer > 21)
				{
					MessageBox.Show("You lose! Dealer wins!");

					gameEnded = true;
					newGame = true;
				}
			}

			else
			{
				MessageBox.Show("You must be dealt cards first!");
			}
			
		}

		private void Surrender(object sender, EventArgs e)
		{
			if (gameEnded)
			{

				MessageBox.Show("Game is ended. You must start a new game.");
			
				return;

			}

			if (dealt)
			{

				MessageBox.Show("You lose! Dealer wins! Game ended.");

				gameEnded = true;
				newGame = true;

			}

			else
			{
				MessageBox.Show("You must be dealt cards first!");
			}
		}

		private void textBox2_TextChanged(object sender, EventArgs e)
		{

		}

		private void label1_Click(object sender, EventArgs e)
		{

		}

		private void textBox1_TextChanged(object sender, EventArgs e)
		{

		}

		private void pictureBox3_Click(object sender, EventArgs e)
		{

		}

		private void New_Game(object sender, EventArgs e)
		{
			if (newGame)
			{

				soundplayer.SoundLocation = ".\\Sounds\\shuffle.wav";

				soundplayer.Play();

				pictureBox1.Image = null;
				pictureBox2.Image = null;
				pictureBox3.Image = null;
				pictureBox4.Image = null;
				pictureBox5.Image = null;
				pictureBox6.Image = null;
				pictureBox7.Image = null;
				pictureBox8.Image = null;
				pictureBox9.Image = null;
				pictureBox10.Image = null;
				pictureBox11.Image = null;

				sumPlayer = 0;
				sumDealer = 0;

				textBox1.Text = null;
				textBox2.Text = null;

				arrayList.Clear();

				dealt = false;
				gameEnded = false;

				firstHit = false;
				secondHit = false;
				thirdHit = false;
				fourthHit = false;
				
				newGame = false;

			}

		}

		private void pictureBox6_Click(object sender, EventArgs e)
		{

		}

	}
}