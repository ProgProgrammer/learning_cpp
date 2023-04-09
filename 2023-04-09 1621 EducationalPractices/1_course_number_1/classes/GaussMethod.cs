using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace _1_course_number_1.classes
{
    internal class GaussMethod
    {
        public GaussMethod() { }

        public List<double> getData(List<double[]> arr_a, List<double> arr_b, int count) 
        {
            double d, s;
            List<double> result = new List<double>();
            result.Add(new double());
            result.Add(new double());
            result.Add(new double());
            result.Add(new double());

            for (int k = 0; k < count; k++) // прямой ход
            {
                for (int j = k + 1; j < count; j++)
                {
                    d = arr_a[j][k] / arr_a[k][k]; // формула (1)

                    for (int i = k; i < count; i++)
                    {
                        arr_a[j][i] = arr_a[j][i] - d * arr_a[k][i]; // формула (2)
                    }

                    arr_b[j] = arr_b[j] - d * arr_b[k]; // формула (3)
                }

            }

            for (int k = count - 1; k >= 1; k--) // обратный ход
            {
                d = 0;

                for (int j = k + 1; j < count; j++)
                {
                    s = arr_a[k][j] * result[j]; // формула (4)
                    d = d + s; // формула (4)
                }

                result[k] = (arr_b[k] - d) / arr_a[k][k]; // формула (4)

            }

            return result;
        }
    }
}
