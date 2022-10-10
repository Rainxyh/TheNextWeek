#include <fstream>
#include <iomanip>
#include <ctime>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include "scene.cpp"

clock_t START_TIME, END_TIME;

vec::vec3 get_color(const ray &ray_, hitable *world, int depth)
{
	hit_record rec;
	// superclass call implemented superclass virtual methods
	if (world->hit(ray_, 0.001, FLT_MAX, rec)) // hitable_list or bvh_node instance, calls its overridden virtual method
	{
		ray scattered;
		vec::vec3 attenuation;
		vec::vec3 emmited = rec.mat_ptr->emitted(rec.u, rec.v, rec.point);
		if (depth < 50 && rec.mat_ptr->scatter(ray_, rec, attenuation, scattered))
		{
			if (typeid(lambertian) == typeid(*rec.mat_ptr->get_class_type()))
			{
				lambertian *temp_ptr = dynamic_cast<lambertian *>(rec.mat_ptr);
				if (typeid(image_texture) == typeid(*temp_ptr->albedo->get_class_type()))
					return attenuation;
			}
			return emmited + attenuation * get_color(scattered, world, depth + 1);
		}
		else
			return emmited;
	}
	else
	{
		// vec::vec3 unit_direction = vec::unit_vector(ray_.direction());
		// float t = 0.5 * (unit_direction.y() + 1.0);
		// return (1.0 - t) * vec::vec3(1, 1, 1) + t * vec::vec3(0.5, 0.7, 1.0);
		return vec::vec3(0);
	}
}

void showProgress(int num, int sum)
{
	// std::cout << "\n";
	std::cout << "\r";
	std::cout << "running: " << (sum - num) * 100 / sum << "%";
}

hitable *fun(camera &cam, std::string &fig_name, hitable *(*func_ptr)(camera &cam, std::string &fig_name))
{
	return func_ptr(cam, fig_name);
}

int main(int argc,char *argv[])
{
	START_TIME = clock();

	std::string fig_name;
	camera camera;
	// hitable *world = TheNextWeek(camera,fig_name);
	hitable *world = fun(camera, fig_name, earth);
	std::string file_path = "./output_fig/";
	if(0!=access(file_path.c_str(),0)){
		if(mkdir(file_path.c_str(),S_IRUSR | S_IWUSR | S_IXUSR | S_IRWXG | S_IRWXO)){
			 std::cerr<< "make dir error"<<std::endl;
		}
	}
	std::ofstream outfile;
	outfile.open(file_path+fig_name+".ppm");
	int nx = 400;
	int ny = 300;
	int ns = 200;
	outfile << "P3\n"
			<< nx << " " << ny << "\n255" << std::endl;

	for (int j = ny; j >= 0; --j)
	{
		showProgress(j, ny);
		for (int i = 0; i < nx; ++i)
		{
			vec::vec3 color(0, 0, 0);
			for (int s = 0; s < ns; ++s) // every pixel random generate ray
			{
				float u = ((float)i + rand_float()) / nx, v = ((float)j + rand_float()) / ny;
				ray ray = camera.get_ray(u, v); // ray's time initial wrong to 0, lead to
				color += get_color(ray, world, 1);
			}
			color /= (float)ns;
			color = gamma_correct(color);
			int ir = int(255.99f * color.r());
			int ig = int(255.99f * color.g());
			int ib = int(255.99f * color.b());
			outfile << ir << " " << ig << " " << ib << std::endl;
		}
	}

	END_TIME = clock();
	double delta_time = (double)(END_TIME - START_TIME) / CLOCKS_PER_SEC;
	std::cout << "Total time " << delta_time << " s" << std::endl;
	return 0;
}
