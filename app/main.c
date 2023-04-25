#include <stdio.h>
#include <time.h>
#include <dlfcn.h>
#include <stdlib.h>
#include <string.h>

#include <zlib.h>
#include <png.h>
#include <freetype.h>

/* Checking extensions of arguments */
void check_ext(char* file) {
	char* ext = strrchr(file, '.');
	if (ext == NULL) {
		printf("[-] This file doesn't have extension: %s\n", file);
		printf("[*] Use flag --help\n");
		exit(EXIT_FAILURE);
	}
	    else {
		  if (strcmp(ext, ".ttf") == 0 || strcmp(ext, ".png") == 0) {
		      printf("[+] Extension correct for: %s\n", file);
		  }
		  else {
		      printf("[-] Extension incorrect for: %s\n", file);
		      printf("[*] Correct extensions: <.ttf> <.png>\nCheck for usage\n");
		      exit(EXIT_FAILURE);
		  }
	    }
}


#define WIDTH 800
#define HEIGHT 600
#define FONT_SIZE 48

int main(int argc, char *argv[]) {
	time_t start_time;
	time(&start_time);
	printf("[*] Start time is: %s", ctime(&start_time));
	clock_t start = clock();
#ifdef _STATIC_
	printf("[!] Static app [!]\n");
#endif	
	
#ifdef _BLOB_
	printf("[!] Blob app [!]\n");
#endif


//todo 
//stab
#ifdef _DYNAMIC_
	printf("[!] Dynamic app [!]\n");
// Initializing libraries in shared format
 	void *zlib_handle = dlopen("libz.so", RTLD_LAZY);
		if (!zlib_handle) {
			fprintf(stderr, "[-] Error loading zlib: %s\n", dlerror());
			exit(EXIT_FAILURE);
    		}
    	void *libpng_handle = dlopen("libpng.so", RTLD_LAZY);
    		if (!libpng_handle) {
    			fprintf(stderr, "[-] Error loading libpng: %s\n", dlerror());
    			exit(EXIT_FAILURE);
    		}
    	void *freetype_handle = dlopen("libfreetype.so", RTLD_LAZY);
    		if (!freetype_handle) {
    			fprintf(stderr, "[-] Error loading freetype: %s\n", dlerror());
    			exit(EXIT_FAILURE);
    		}
// Initializing and loading from data functions that provided from libpng, freetype, zlib
	typedef FT_Error (*FT_Init_FreeType_func)(FT_Library *library);
	FT_Init_FreeType_func FT_Init_FreeType = dlsym(freetype_handle, "FT_Init_FreeType");
	if (!FT_Init_FreeType) {
	    fprintf(stderr, "[-] Error loading function: FT_Init_FreeType\n");
	    exit(EXIT_FAILURE);
	}
	typedef FT_Error (*FT_New_Face_func)(FT_Library library, const char* filepathname, FT_Long face_index, FT_Face *aface);
	FT_New_Face_func FT_New_Face = dlsym(freetype_handle, "FT_New_Face");
	typedef FT_Error (*FT_Set_Pixel_Sizes_func)(FT_Face face, FT_UInt pixel_width, FT_UInt pixel_height);
	FT_Set_Pixel_Sizes_func FT_Set_Pixel_Sizes = dlsym(freetype_handle, "FT_Set_Pixel_Sizes");
	typedef FT_UInt (*FT_Get_Char_Index_func)(FT_Face face, FT_ULong charcode);
	FT_Get_Char_Index_func FT_Get_Char_Index = dlsym(freetype_handle, "FT_Get_Char_Index");
	typedef FT_Error (*FT_Load_Glyph_func)(FT_Face face, FT_UInt glyph_index, FT_Int32 load_flags);
	FT_Load_Glyph_func FT_Load_Glyph = dlsym(freetype_handle, "FT_Load_Glyph");
	typedef void (*FT_Done_Face_func)(FT_Face face);
	FT_Done_Face_func FT_Done_Face = dlsym(freetype_handle, "FT_Done_Face");
	typedef void (*FT_Done_FreeType_func)(FT_Library library);
	FT_Done_FreeType_func FT_Done_FreeType = dlsym(freetype_handle, "FT_Done_FreeType");
	
	png_structp (*png_create_write_struct)(png_const_charp user_png_ver, png_voidp error_ptr, png_error_ptr error_fn, png_error_ptr warn_fn);
	png_infop (*png_create_info_struct)(png_structp png_ptr);
	void (*png_init_io)(png_structp png_ptr, FILE *fp);
	void (*png_set_IHDR)(png_structp png_ptr, png_infop info_ptr, png_uint_32 width, png_uint_32 height, int bit_depth, int color_type, int interlace_type, int compression_type, int filter_type);
	void (*png_write_info)(png_structp png_ptr, png_infop info_ptr);
	void (*png_write_image)(png_structp png_ptr, png_bytepp image);
	void (*png_write_end)(png_structp png_ptr, png_infop info_ptr);
	
	    png_create_write_struct = dlsym(libpng_handle, "png_create_write_struct");
	    if (!png_create_write_struct) {
		  fprintf(stderr, "[-] Error loading function: png_create_write_struct\n");
		  exit(EXIT_FAILURE);
	    }

	    png_create_info_struct = dlsym(libpng_handle, "png_create_info_struct");
	    if (!png_create_info_struct) {
		  fprintf(stderr, "[-] Error loading function: png_create_info_struct\n");
		  exit(EXIT_FAILURE);
	    }

	    png_init_io = dlsym(libpng_handle, "png_init_io");
	    if (!png_init_io) {
		  fprintf(stderr, "[-] Error loading function: png_init_io\n");
		  exit(EXIT_FAILURE);
	    }

	    png_set_IHDR = dlsym(libpng_handle, "png_set_IHDR");
	    if (!png_set_IHDR) {
		  fprintf(stderr, "[-] Error loading function: png_set_IHDR\n");
		  exit(EXIT_FAILURE);
	    }

	    png_write_info = dlsym(libpng_handle, "png_write_info");
	    if (!png_write_info) {
		  fprintf(stderr, "[-] Error loading function: png_write_info\n");
		  exit(EXIT_FAILURE);
	    }

	    png_write_image = dlsym(libpng_handle, "png_write_image");
	    if (!png_write_image) {
		  fprintf(stderr, "[-] Error loading function: png_write_image\n");
		  exit(EXIT_FAILURE);
	    }

	    png_write_end = dlsym(libpng_handle, "png_write_end");
	    if (!png_write_end) {
		  fprintf(stderr, "[-] Error loading function: png_write_end\n");
		  exit(EXIT_FAILURE);
	    }

#endif


#ifdef _BLOB_
	// TODO:
	// Create table structure
	// How elf-loader works
	// What should implement in code
	
#endif
char *font_file;
	char *image_file;
	char *text;
	if (strcmp(argv[1], "--help") == 0) {
		printf("Usage: ./app-static.bin <*.ttf> <*.png> <sample_text>\n");
		printf("\t1 arg - font\n\t2 arg - name of png file\n\t3 arg - text that you want to see\n");
		exit(EXIT_FAILURE);
	}
	
	if (argc != 4) {
		printf("Usage: %s <*.ttf> <*.png> <sample_text>\n", argv[0]);
		return 1;
	}
	else {
		font_file = argv[1]; 
		image_file = argv[2];
		text = argv[3];
	}

	check_ext(font_file);
	check_ext(image_file);


// Freetype initializing fonts
	FT_Library library;
	FT_Face face;

	FT_Error error = FT_Init_FreeType(&library);

	if (error) {
		printf("[-] Error: Failed to load FreeType library\n");
		exit(EXIT_FAILURE);
	}
	
	char font_path[256] = "/home/f7kso/lab1/src/fonts/";
	strcpy(font_path + strlen(font_path), font_file);
	printf("font_path: %s\n", font_path);
		
	error = FT_New_Face( library,	font_path, 0, &face);
	if ( error == FT_Err_Unknown_File_Format )
	{
		printf("[-] Error: Unsupported font file format\n");
		exit(EXIT_FAILURE);
	}
	else if ( error )
	{
		printf("[-] Error: Failed to load font file\n");
		exit(EXIT_FAILURE);
	}
	
	error = FT_Set_Pixel_Sizes(face, 0, 48);
	if (error) {
		printf("[-] Error: Failed to set font size\n");
		exit(EXIT_FAILURE);
      }
	
	printf("num_glyphs: %ld\n", face->num_glyphs);
	
// Set font size
	error = FT_Set_Pixel_Sizes(face, 0, FONT_SIZE);
	if (error) {
		printf("Failed to set font size\n");
		exit(EXIT_FAILURE);
	}
	
// Create image
	png_bytep *rows = malloc(HEIGHT * sizeof(png_bytep));
	for (int y = 0; y < HEIGHT; y++) {
		rows[y] = malloc(WIDTH * 4);
		memset(rows[y], 0, WIDTH * 4);
	}
	
// Render text
	int pen_x = 20, pen_y = 50;
	for (int i = 0; i < strlen(text); i++) {
	    FT_UInt glyph_index = FT_Get_Char_Index(face, text[i]);
	    FT_Error error = FT_Load_Glyph(face, glyph_index, FT_LOAD_RENDER);
	    if (error) {
		  printf("Failed to load glyph\n");
		  continue;
	    }

	    FT_Bitmap bitmap = face->glyph->bitmap;
	    for (int y = 0; y < bitmap.rows; y++) {
		  for (int x = 0; x < bitmap.width; x++) {
		      int pos_x = pen_x + face->glyph->bitmap_left + x;
		      int pos_y = pen_y - face->glyph->bitmap_top + y;
		      if (pos_x >= 0 && pos_x < WIDTH && pos_y >= 0 && pos_y < HEIGHT) {
		          rows[pos_y][pos_x * 4] = 255;
		          rows[pos_y][pos_x * 4 + 1] = 255;
		          rows[pos_y][pos_x * 4 + 2] = 255;
		          rows[pos_y][pos_x * 4 + 3] = bitmap.buffer[y * bitmap.width + x];
		      }
		  }
	    }
	    
		if (pen_x >= WIDTH-100) {
			pen_x = 20;
			pen_y += 48;
		if (pen_y >= HEIGHT) {
			break;
		}
	}

	    pen_x += (face->glyph->advance.x >> 6);
	}
// Write image to file
	FILE *fp = fopen(image_file, "wb");
	if (!fp) {
	    printf("Failed to open file\n");
	    exit(EXIT_FAILURE);
	}

	png_structp png_ptr = png_create_write_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
	if (!png_ptr) {
	    printf("Failed to create png write struct\n");
	    exit(EXIT_FAILURE);
	}

	png_infop info_ptr = png_create_info_struct(png_ptr);
	if (!info_ptr) {
	    printf("Failed to create png info struct\n");
	    exit(EXIT_FAILURE);
	}

	png_init_io(png_ptr, fp);
	png_set_IHDR(png_ptr, info_ptr, WIDTH, HEIGHT, 8, PNG_COLOR_TYPE_RGB_ALPHA, PNG_INTERLACE_NONE, PNG_COMPRESSION_TYPE_BASE, PNG_FILTER_TYPE_BASE);
	png_write_info(png_ptr, info_ptr);
	png_write_image(png_ptr, rows);
	png_write_end(png_ptr, NULL);

	fclose(fp);
	printf("Image saved to %s\n", image_file);

// Free memory
	for (int y = 0; y < HEIGHT; y++) {
	    free(rows[y]);
	}
	free(rows);
	FT_Done_Face(face);
	FT_Done_FreeType(library);
	

	printf("[*] Font: %s\n", font_file);
	printf("[*] Image: %s\n", image_file);
	printf("[*] User text: %s\n", text);
	
	time_t end_time;
	time(&end_time);
	printf("[*] End time is: %s", ctime(&end_time));
	
	clock_t end = clock();
    	double time_spent = (double)(end - start) / CLOCKS_PER_SEC;
	printf("[*] Execution time: %f seconds.\n", time_spent);
	return 0;
}
