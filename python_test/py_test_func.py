import math
import warnings

class pyTestFunc:

	@staticmethod
	def test_matrix(mat_one, mat_two):
		'''compare two matrix and return True if they are equal
		'''
		if len(mat_one) != len(mat_two):
			warnings.warn("Size of Axis=0 is not equal")
			return False
		for i, mat_one_i in enumerate(mat_one):
			if len(mat_one_i) != len(mat_two[i]):
				warnings.warn(f"Size of Axis=1 is not equal at index [{i}]")
				return False
			for j, mat_one_i_j in enumerate(mat_one_i):
				if not math.isclose(mat_one_i_j, mat_two[i][j]): # default rel_tol=1e-09, abs_tol=0.0
					warnings.warn(f"Value is not equal at index [{i}][{j}], {mat_one_i_j} != {mat_two[i][j]}")
					return False
		return True

	@staticmethod
	def test_vector(vec_one, vec_two):
		'''compare two vector and return True if they are equal
		'''
		if len(vec_one) != len(vec_two):
			warnings.warn("Size of vector is not equal")
			return False
		for i, vec_one_i in enumerate(vec_one):
			if not math.isclose(vec_one_i, vec_two[i]): # default rel_tol=1e-09, abs_tol=0.0
				warnings.warn(f"Value is not equal at index [{i}], {vec_one_i} != {vec_two[i]}")
				return False
		return True

	@staticmethod
	def heatmap_gauss(fix_x, fix_y, fix_dur, win_x, win_y, sigma_factor=1):
		'''ganca::heatmap::heatmapGauss()
		'''
		heat_map = [[0 for i in range(win_y)] for j in range(win_x)]
		for i, _ in enumerate(fix_x):
			sigma = fix_dur[i] / sigma_factor
			for x in range(win_x):
				for y in range(win_y):
					dist = ((x - fix_x[i])**2 + (y - fix_y[i])**2)**0.5
					heat_map[x][y] += math.exp(-dist**2/(2*sigma**2)) / (sigma*(math.pi*2)**0.5)
		for x in range(win_x):
			for y in range(win_y):
				heat_map[x][y] /= len(fix_x)

		return heat_map

	@staticmethod
	def display_area_to_px(coords_abs, resolution):
		return coords_abs * resolution

	@staticmethod
	def cnt_raster_aoi(aoi_mask, fix_x, fix_y, win_x, win_y):
		'''ganca::AOIHit::cntRasterAOI()
		'''
		is_inside = [False for _ in range(len(fix_x))]

		for x, col_x in enumerate(aoi_mask):
			for y, pnt_xy in enumerate(col_x):
				aoi_mask[x][y] = 1 if pnt_xy - 0.5 > 0 else 0

		for i, _ in enumerate(fix_x):
			if fix_x[i] < 0 or fix_x[i] >= win_x or fix_y[i] < 0 or fix_y[i] >= win_y:
				is_inside[i] = False
				continue

			is_inside[i] = True if aoi_mask[int(fix_x[i])][int(fix_y[i])] == 1 else False

		return is_inside


class pyTestFixationFilter:
	'''ganca::fixationfilter::FixationFilter
	'''
	def __init__(self,
			time_stamp_in,
			validity_in,
			gaze_vector_x,
			gaze_vector_y,
			gaze_vector_z,
		):
		'''ganca::fixationfilter::FixationFilter::FixationFilter()
		'''
		# input
		self.time_stamp_in = time_stamp_in
		self.validity_in = validity_in
		self.gaze_vector_x = gaze_vector_x
		self.gaze_vector_y = gaze_vector_y
		self.gaze_vector_z = gaze_vector_z

		# output
		self.is_fixation = []
		self.validity_out = []
		self.time_stamp_out = []
		self.velocity = []

		# parameters
		self.velocity_threshold = None


	def IVT_filter(self, velocity_threshold):
		'''ganca::fixationfilter::FixationFilter::IVT_filter()
		'''
		self.velocity_threshold = velocity_threshold
		self.is_fixation = [False for _ in range(len(self.time_stamp_in)-1)]
		self.validity_out = [False for _ in range(len(self.time_stamp_in)-1)]
		self.time_stamp_out = [0 for _ in range(len(self.time_stamp_in)-1)]
		self.velocity = [0 for _ in range(len(self.time_stamp_in)-1)]

		for i, _ in enumerate(self.time_stamp_in[:-1]):
			self.time_stamp_out[i] = (self.time_stamp_in[i] + self.time_stamp_in[i + 1]) / 2

			if not self.validity_in[i] or not self.validity_in[i + 1]:
				continue

			self.velocity[i] = math.acos((
					self.gaze_vector_x[i] * self.gaze_vector_x[i+1]
					+ self.gaze_vector_y[i] * self.gaze_vector_y[i+1]
					+ self.gaze_vector_z[i] * self.gaze_vector_z[i+1]
				) / (
					math.sqrt(self.gaze_vector_x[i]**2 + self.gaze_vector_y[i]**2 + self.gaze_vector_z[i]**2)
					* math.sqrt(self.gaze_vector_x[i+1]**2 + self.gaze_vector_y[i+1]**2 + self.gaze_vector_z[i+1]**2)
				) / (self.time_stamp_in[i+1] - self.time_stamp_in[i]))

			if self.velocity[i] < self.velocity_threshold:
				self.is_fixation[i] = True
				self.validity_out[i] = True